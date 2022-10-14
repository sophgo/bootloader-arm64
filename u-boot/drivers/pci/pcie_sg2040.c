/****************************************************************************
 * SPDX-License-Identifier: GPL-2.0+
 *
 * Copyright 2021-2025 Sophgo
 *
 * PCIe Gen4 driver for Sophgo Mango SoC
 * Author: lifengchun <fengchun.li@sophgo.com>
 *
 ****************************************************************************/
#include <common.h>
#include <pci.h>
#include <dm.h>
#include <asm/io.h>
#include <errno.h>
#include <malloc.h>
#include <linux/sizes.h>
#include <linux/ioport.h>
#include <linux/log2.h>
#include "pcie_sg2040.h"
#include "pci_ep.h"

DECLARE_GLOBAL_DATA_PTR;

LIST_HEAD(cdns_pcie_list);

static u64 bar_max_size[] = {
	[RP_BAR0] = _ULL(128 * SZ_2G),
	[RP_BAR1] = SZ_2G,
	[RP_NO_BAR] = _BITULL(63),
};

static u8 bar_aperture_mask[] = {
	[RP_BAR0] = 0x1F,
	[RP_BAR1] = 0xF,
};

struct pci_bar epf_bar[6];

struct cdns_pcie *g_pcie;

struct cdns_pcie *cdns_get_pcie(void)
{
	return g_pcie;
}

static int cdns_pcie_ltssm(struct cdns_pcie *pcie)
{
	u32 state;
	u32 apb_base;

	apb_base = CDNS_PCIE_CFG_MANGO_APB;

	state = cdns_pcie_readl(pcie, (apb_base + CDNS_PCIE_IRS_REG00C0));
	state = (state & LINK0_LTSSM_STATE_MASK) >> 3;

	return state;
}

static int cdns_pcie_link_up(struct cdns_pcie *pcie)
{
	int ltssm;

	ltssm = cdns_pcie_ltssm(pcie);
	if (ltssm != CDNS_PCIE_LTSSM_L0)
		return 0;

	return 1;
}

#if 0
static void cdns_pcie_ep_enable_cfg(struct cdns_pcie *pcie)
{
	//ccsr_writel(pcie, GPEX_CFG_READY, PCIE_CONFIG_READY);
}
#endif

/****************************************************************************
 *       PCIE_Are_There_Local_Errors
 *
 * API function to check if there are any local errors
 ****************************************************************************/
int cdns_pcie_are_there_local_err(struct cdns_pcie *pcie, cnds_pcie_bool *p_err, uint32_t *p_type)
{
	int result = 0;
	u32 apb_base = 0;

	/* Check input parameters are not NULL */
	if ((pcie == NULL) || (p_err == NULL) || (p_type == NULL)) {
		return -EINVAL;
	}

	/* Read register from PCIe IP */
	apb_base = CDNS_PCIE_CFG_LINK0_APB + CDNS_PCIE_LM_OFFSET;
	*p_type = cdns_pcie_readl(pcie, (apb_base + LM_LOCAL_ERR_STS_REG));

	if (*p_type != 0U) {
		*p_err = CDNS_PCIE_TRUE;
	} else {
		*p_err = CDNS_PCIE_FALSE;
	}

	return result;
}

static uint32_t cdns_pcie_call_error_hdl(struct cdns_pcie *pcie)
{
	cdns_pcie_bool le;
	uint32_t et;
	int result = 0;

	if (cdns_pcie_are_there_local_err(pcie, &le, &et) != 0U) {
		return -EINVAL;
	}

	if (le == CDNS_PCIE_TRUE) {
		printf("CallbackHandler Called with status 0x%x\n", et);
	}

	return result;
}

/*****************************************************************************
 * Local function for ECAM Transfer Config Check
 *****************************************************************************/
static cdns_pcie_bool cdns_pcie_ecam_transfer_cfg_check(const transfer_cfg_data *ptransfer_cfg)
{
	return ((((ptransfer_cfg->bus) > (uint16_t)PCIE_ECAM_MAX_BUS) ||
		 ((ptransfer_cfg->dev) > (uint16_t)PCIE_ECAM_MAX_DEV) ||
		 ((ptransfer_cfg->func) > (uint16_t)PCIE_ECAM_MAX_FUNC) ||
		 ((ptransfer_cfg->offset) > (uint32_t)PCIE_ECAM_MAX_OFFSET))
		? CDNS_PCIE_TRUE : CDNS_PCIE_FALSE);
}

static int cdns_pcie_ecam_config_read(void *pcie_addr, uint32_t *val,
				      enum pci_size_t size, const transfer_cfg_data *ptransfer_cfg)
{
	void *eaddr = NULL;
	int result = 0;
	int byte_seq = 0;
	uint32_t temp_addr = 0;
	uint32_t value = 0;

	if ((val == NULL) || (ptransfer_cfg == NULL) ||
	    (cdns_pcie_ecam_transfer_cfg_check(ptransfer_cfg) == CDNS_PCIE_TRUE)) {
		return -EINVAL;
	}

	temp_addr = ECAMADDR((uintptr_t)(ptransfer_cfg->bus), (uintptr_t)(ptransfer_cfg->dev),
			     (uintptr_t)(ptransfer_cfg->func), (uintptr_t)(ptransfer_cfg->offset));
	eaddr = pcie_addr + ((temp_addr >> 2) << 2);
	value = readl((volatile u32*)eaddr);
	byte_seq = ptransfer_cfg->offset & 0x3;

	/* read the required width */
	switch (size) {
	case PCI_SIZE_8:
		*val = (value >> (byte_seq * 8)) & 0xFF;
		break;
	case PCI_SIZE_16:
		*val = (value >> (byte_seq * 8)) & 0xFFFF;
		break;
	case PCI_SIZE_32:
		*val = value;
		break;
	default:
		result = -EINVAL;
		break;
	}

	return result;
}

static int cdns_pcie_read_config(const struct udevice *bus, pci_dev_t bdf,
				 uint offset, ulong *valuep, enum pci_size_t size)
{
	struct cdns_pcie *pcie = dev_get_priv(bus);
	uint32_t var = 0;
	int result = 0;
	void *pcie_addr = NULL;

	bdf = bdf >> 8;
	transfer_cfg_data stransfer_cfg = {
		/* get upper 8 bits from BDF and shift right */
		.bus = ((bdf & 0xFF00U) >> 8U),
		/* get 5 dev bits from BDF and shift right */
		.dev = ((bdf & 0x00F8U) >> 3U),
		/* get 3 func bits from BDF */
		.func = (bdf & 0x0007U),
		.offset = offset,
	};

	if (valuep == NULL) {
		return -EINVAL;
	}

	if (bdf == 0) {
		pcie_addr = pcie->reg_base + CDNS_PCIE_CFG_LINK0_APB + CDNS_PCIE_RP_OFFSET;
	} else {
		pcie_addr = pcie->cfg_base;
	}

	if (cdns_pcie_ecam_config_read(pcie_addr, &var, size,  &stransfer_cfg) != 0U) {
		*valuep = 0;
		return -EINVAL;
	}

	*valuep = var;

	return result;
}

static int cdns_pcie_ecam_config_write(void *pcie_addr, ulong data,
				       enum pci_size_t size, const transfer_cfg_data *ptransfer_cfg)
{
	void *eaddr = NULL;
	int result = 0;
	int byte_seq = 0;
	uint32_t temp_addr = 0;
	uint32_t value = 0;

	if ((ptransfer_cfg == NULL) ||
	    (cdns_pcie_ecam_transfer_cfg_check(ptransfer_cfg) == CDNS_PCIE_TRUE)) {
		return -EINVAL;
	}

	/* Hardware is strapped (only) for ECAM addressing */
	temp_addr = ECAMADDR((uintptr_t)(ptransfer_cfg->bus), (uintptr_t)(ptransfer_cfg->dev),
			     (uintptr_t)(ptransfer_cfg->func), (uintptr_t)(ptransfer_cfg->offset));
	eaddr = pcie_addr + ((temp_addr >> 2) << 2);
	byte_seq = ptransfer_cfg->offset & 0x3;

	/* write the required width */
	switch (size) {
	case PCI_SIZE_8:
		value = readl((volatile u32*)eaddr);
		value = value | ((data & 0xFF) << byte_seq * 8);
		writel(value, (volatile u8*)eaddr);
		break;
	case PCI_SIZE_16:
		value = readl((volatile u32*)eaddr);
		value = value | ((data & 0xFF) << byte_seq * 8);
		writel(value, (volatile u16*)eaddr);
		break;
	case PCI_SIZE_32:
		writel(data, (volatile u32*)eaddr);
		break;
	default:
		result = -EINVAL;
		break;
	}

	if (result == 0) {
		/* Check for errors reported from PCIe IP */
		result = cdns_pcie_call_error_hdl(g_pcie);
	}

	return result;
}

static int cdns_pcie_write_config(struct udevice *bus, pci_dev_t bdf,
				  uint offset, ulong value, enum pci_size_t size)
{
	struct cdns_pcie *pcie = dev_get_priv(bus);
	int result = 0;
	void *pcie_addr = NULL;

	bdf = bdf >> 8;
	transfer_cfg_data stransfer_cfg = {
		/* get upper 8 bits from BDF and shift right */
		.bus = ((bdf & 0xFF00U) >> 8U),
		/* get 5 dev bits from BDF and shift right */
		.dev = ((bdf & 0x00F8U) >> 3U),
		/* get 3 func bits from BDF */
		.func = (bdf & 0x0007U),
		.offset = offset,
	};

	if (bdf == 0) {
		pcie_addr = pcie->reg_base + CDNS_PCIE_CFG_LINK0_APB + CDNS_PCIE_RP_OFFSET;
	} else {
		pcie_addr = pcie->cfg_base;
	}

	if (cdns_pcie_ecam_config_write(pcie_addr, value, size, &stransfer_cfg) != 0U) {
		return -EINVAL;
	}

	return (result);
}

static int cdns_pcie_outbound_win_set(struct cdns_pcie *pcie,
				      u32 region, cdns_pcie_bool is_io, u64 cpu_addr, u64 pci_addr, size_t size)
{
	/* roundup_pow_of_two() returns an unsigned long, which is not suited for 64bit values. */
	u64 sz = 1ULL << fls64(size - 1);
	int nbits = ilog2(sz);
	u32 addr0, addr1, desc0, desc1;
	u32 apb_base = 0;

	if (nbits < 8) {
		nbits = 8;
	}

	apb_base =  CDNS_PCIE_CFG_LINK0_APB;
	/* Set the PCI address */
	addr0 = CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS(nbits) |
		(lower_32_bits(pci_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(pci_addr);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(apb_base, region), addr0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(apb_base, region), addr1);

	/* Set the PCIe header descriptor */
	if (is_io) {
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_IO;
	} else {
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MEM;
	}
	desc1 = 0;

	if (region == 0) {
		desc0 = CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE0;
	}

	/*
	 * Whatever Bit [23] is set or not inside DESC0 register of the outbound
	 * PCIe descriptor, the PCI function number must be set into
	 * Bits [26:24] of DESC0 anyway.
	 *
	 * In Root Complex mode, the function number is always 0 but in Endpoint
	 * mode, the PCIe controller may support more than one function. This
	 * function number needs to be set properly into the outbound PCIe
	 * descriptor.
	 *
	 * Besides, setting Bit [23] is mandatory when in Root Complex mode:
	 * then the driver must provide the bus, resp. device, number in
	 * Bits [7:0] of DESC1, resp. Bits[31:27] of DESC0. Like the function
	 * number, the device number is always 0 in Root Complex mode.
	 *
	 * However when in Endpoint mode, we can clear Bit [23] of DESC0, hence
	 * the PCIe controller will use the captured values for the bus and
	 * device numbers.
	 */
	if (pcie->is_rc) {
		/* The device and function numbers are always 0. */
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID |
			 CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(0);
		desc1 |= CDNS_PCIE_AT_OB_REGION_DESC1_BUS(0);
	} else {
		/*
		 * Use captured values for bus and device numbers but still
		 * need to set the function number.
		 */
		desc0 |= CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(0);
	}

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_DESC0(apb_base, region), desc0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_DESC1(apb_base, region), desc1);

	/* Set the CPU address */
	addr0 = CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(nbits) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);

	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(apb_base, region), addr0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(apb_base, region), addr1);

	return 0;
}

static int cdns_pcie_rc_inbound_win_set(struct cdns_pcie *pcie, enum cdns_pcie_rp_bar bar,
					u64 cpu_addr, u64 size, unsigned long flags)
{
	u32 addr0, addr1, aperture, value;
	u32 apb_base = 0;

	if (pcie->avail_ib_bar[bar])
		return -EBUSY;

	apb_base =  CDNS_PCIE_CFG_LINK0_APB;
	pcie->avail_ib_bar[bar] = false;

	aperture = ilog2(size);
	addr0 = CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS(aperture) |
		(lower_32_bits(cpu_addr) & GENMASK(31, 8));
	addr1 = upper_32_bits(cpu_addr);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_IB_RP_BAR_ADDR0(apb_base, bar), addr0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_IB_RP_BAR_ADDR1(apb_base, bar), addr1);

	if (bar == RP_NO_BAR)
		return 0;

	value = cdns_pcie_readl(pcie, CDNS_PCIE_LM_RC_BAR_CFG);
	value &= ~(LM_RC_BAR_CFG_CTRL_MEM_64BITS(bar) |
		LM_RC_BAR_CFG_CTRL_PREF_MEM_64BITS(bar) |
		LM_RC_BAR_CFG_CTRL_MEM_32BITS(bar) |
		LM_RC_BAR_CFG_CTRL_PREF_MEM_32BITS(bar) |
		LM_RC_BAR_CFG_APERTURE(bar, bar_aperture_mask[bar] + 2));
	if (size + cpu_addr >= SZ_4G) {
		if (!(flags & IORESOURCE_PREFETCH))
			value |= LM_RC_BAR_CFG_CTRL_MEM_64BITS(bar);
		value |= LM_RC_BAR_CFG_CTRL_PREF_MEM_64BITS(bar);
	} else {
		if (!(flags & IORESOURCE_PREFETCH))
			value |= LM_RC_BAR_CFG_CTRL_MEM_32BITS(bar);
		value |= LM_RC_BAR_CFG_CTRL_PREF_MEM_32BITS(bar);
	}

	value |= LM_RC_BAR_CFG_APERTURE(bar, aperture);
	cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_LM_RC_BAR_CFG), value);

	return 0;
}

static void cdns_pcie_setup_wins(struct cdns_pcie *pcie)
{
	u64 /*cpu_addr, pci_addr, size,*/winsize;
	struct pci_region *io, *mem, *pref;
	unsigned long flags = 0;
	u32 region = 0;
	u32 result = 0;

	/* INBOUND WIN */
	winsize = bar_max_size[RP_BAR0];
	cdns_pcie_rc_inbound_win_set(pcie, RP_BAR0, 0, winsize, flags);
	winsize = bar_max_size[RP_BAR1];
	cdns_pcie_rc_inbound_win_set(pcie, RP_BAR1, 0, winsize, flags);
	winsize = bar_max_size[RP_NO_BAR];
	cdns_pcie_rc_inbound_win_set(pcie, RP_NO_BAR, 0, winsize, flags);

	/* OUTBOUND WIN 0: CFG */
	region = 0;
	cdns_pcie_outbound_win_set(pcie, region, CDNS_PCIE_FALSE,
				   pcie->cfg_res.start, pcie->cfg_res.start, fdt_resource_size(&pcie->cfg_res));

	result = pci_get_regions(pcie->bus, &io, &mem, &pref);
	if (result == 0) {
		return;
	}

	if (mem) {
		/* OUTBOUND WIN: MEM */
		region = 1;
		cdns_pcie_outbound_win_set(pcie, region, CDNS_PCIE_FALSE,
					   mem->phys_start, mem->bus_start, mem->size);
	}
	if (io) {
		/* OUTBOUND WIN: IO */
		region = 2;
		cdns_pcie_outbound_win_set(pcie, region, CDNS_PCIE_TRUE,
					   io->phys_start, io->bus_start, io->size);
	}
}

static int cdns_pcie_host_init_root_port(struct cdns_pcie *pcie)
{
	u32 value, ctrl;
	u32 id;
	u32 apb_base = 0;

	apb_base =  CDNS_PCIE_CFG_LINK0_APB;
	/*
	 * Set the root complex BAR configuration register:
	 * - disable both BAR0 and BAR1.
	 * - enable Prefetchable Memory Base and Limit registers in type 1
	 *   config space (64 bits).
	 * - enable IO Base and Limit registers in type 1 config
	 *   space (32 bits).
	 */
	ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED;
	value = CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL(ctrl) |
		CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL(ctrl) |
		CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_ENABLE |
		CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_64BITS |
		CDNS_PCIE_LM_RC_BAR_CFG_IO_ENABLE |
		CDNS_PCIE_LM_RC_BAR_CFG_IO_32BITS;
	cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_LM_RC_BAR_CFG), value);

	/* Set root port configuration space */
	//if (pcie->vendor_id != 0xffff) {
	//    id = CDNS_PCIE_LM_ID_VENDOR(pcie->vendor_id)
	//         | CDNS_PCIE_LM_ID_SUBSYS(pcie->vendor_id);
	//    cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_LM_ID), id);
	//}

	//if (pcie->device_id != 0xffff)
	//    cdns_pcie_rp_writew(pcie, (apb_base + PCI_DEVICE_ID), pcie->device_id);

	///cdns_pcie_rp_writeb(pcie, (apb_base + PCI_CLASS_REVISION), 0);
	//cdns_pcie_rp_writeb(pcie, (apb_base + PCI_CLASS_PROG), 0);
	cdns_pcie_rp_writel(pcie, (apb_base + PCI_REVISION_ID), (PCI_CLASS_BRIDGE_CARDBUS << 16));

	return 0;
}

static int cdns_pcie_mapping(struct cdns_pcie *pcie)
{
	u32 apb_base = 0;

	apb_base =  CDNS_PCIE_CFG_MANGO_APB;

	//pcie addr mapping
	cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_IRS_REG0400), 0x00000000);
	cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_IRS_REG0404), 0x20);
	cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_IRS_REG0418), 0xffffffff);
	cdns_pcie_writel(pcie, (apb_base + CDNS_PCIE_IRS_REG041C), 0x3f);

	return 0;
}

static int cdns_pcie_setup_ctrl(struct cdns_pcie *pcie)
{
	int err;
	const void *fdt = gd->fdt_blob;
	int node = dev_of_offset(pcie->bus);
	int ret;

	ret = fdt_get_named_resource(fdt, node, "reg", "reg-names", "cfg", &pcie->cfg_res);
	if (ret) {
		printf("cdns_pcie: resource \"config\" not found\n");
		return ret;
	}

	pcie->cfg_base = map_physmem(pcie->cfg_res.start,
				     fdt_resource_size(&pcie->cfg_res), MAP_NOCACHE);
	printf("%s: cfg_res start 0x%llx, cfg_base = 0x%p\n", __func__, pcie->cfg_res.start, pcie->cfg_base);

	err = cdns_pcie_host_init_root_port(pcie);
	if (err)
		return err;

	cdns_pcie_setup_wins(pcie);
	cdns_pcie_mapping(pcie);

	return 0;
}

static void cdns_pcie_ep_inbound_win_set(struct cdns_pcie *pcie, int pf, int bar, u64 phys)
{
	//u32 val;
#if 0
	/* PF BAR1 is for MSI-X and only need to enable */
	if (bar == 1) {
		ccsr_writel(pcie, PAB_PEX_BAR_AMAP(pf, bar), BAR_AMAP_EN);
		return;
	}

	val = upper_32_bits(phys);
	cdns_pcie_writel(pcie, PAB_EXT_PEX_BAR_AMAP(pf, bar), val);
	val = lower_32_bits(phys) | BAR_AMAP_EN;
	cdns_pcie_writel(pcie, PAB_PEX_BAR_AMAP(pf, bar), val);
#endif
}

static void cdns_pcie_ep_setup_wins(struct cdns_pcie *pcie, int pf)
{
	u64 phys;
	int bar;
	//u32 val;
	u32 region = 0;
	u64 cpu_addr = 0;
	u64 pci_addr = 0;
	size_t size = 0;

	//if ((!pcie->sriov_support && pf > LS_G4_PF0) || pf > LS_G4_PF1)
	//return;

	//phys = CONFIG_SYS_PCI_EP_MEMORY_BASE + PCIE_BAR_SIZE * 4 * pf;
	for (bar = 0; bar < CDNS_PF_BAR_NUM; bar++) {
		cdns_pcie_ep_inbound_win_set(pcie, pf, bar, phys);
		phys += CDNS_PCIE_BAR_SIZE;
	}

	/* OUTBOUND: map MEM */
	cdns_pcie_outbound_win_set(pcie, region, CDNS_PCIE_FALSE, cpu_addr, pci_addr, size);
#if 0
	val = cdns_pcie_readl(pcie, PAB_AXI_AMAP_PCI_HDR_PARAM(pf));
	val &= ~FUNC_NUM_PCIE_MASK;
	val |= pf;
	cdns_pcie_writel(pcie, PAB_AXI_AMAP_PCI_HDR_PARAM(pf), val);
#endif
}

static int cdns_pcie_ep_set_bar(struct cdns_pcie *pcie, u8 fn, struct pci_bar *epf_bar)
{
	struct cdns_pcie_epf *epf = pcie->epf;
	dma_addr_t bar_phys = epf_bar->phys_addr;
	enum pci_barno bar = epf_bar->barno;
	int flags = epf_bar->flags;
	u32 addr0, addr1, reg, cfg, b, aperture, ctrl;
	u64 sz;

	/* BAR size is 2^(aperture + 7) */
	sz = max_t(size_t, epf_bar->size, CDNS_PCIE_EP_MIN_APERTURE);
	/* roundup_pow_of_two() returns an unsigned long, which is not suited
	 * for 64bit values.
	 */
	sz = 1ULL << fls64(sz - 1);
	aperture = ilog2(sz) - 7; /* 128B -> 0, 256B -> 1, 512B -> 2, ... */

	if ((flags & PCI_BASE_ADDRESS_SPACE) == PCI_BASE_ADDRESS_SPACE_IO) {
		ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_IO_32BITS;
	} else {
		bool is_prefetch = !!(flags & PCI_BASE_ADDRESS_MEM_PREFETCH);
		bool is_64bits = sz > SZ_2G;

		if (is_64bits && (bar & 1)) {
			return -EINVAL;
		}

		if (is_64bits && !(flags & PCI_BASE_ADDRESS_MEM_TYPE_64))
			epf_bar->flags |= PCI_BASE_ADDRESS_MEM_TYPE_64;

		if (is_64bits && is_prefetch)
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS;
		else if (is_prefetch)
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS;
		else if (is_64bits)
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_64BITS;
		else
			ctrl = CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_32BITS;
	}

	addr0 = lower_32_bits(bar_phys);
	addr1 = upper_32_bits(bar_phys);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar), addr0);
	cdns_pcie_writel(pcie, CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar), addr1);
	if (bar < BAR_4) {
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG0(fn);
		b = bar;
	} else {
		reg = CDNS_PCIE_LM_EP_FUNC_BAR_CFG1(fn);
		b = bar - BAR_4;
	}

	cfg = cdns_pcie_readl(pcie, reg);
	cfg &= ~(CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
		CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
	cfg |= (CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE(b, aperture) |
		CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl));
	cdns_pcie_writel(pcie, reg, cfg);

	epf->epf_bar[bar] = epf_bar;

	return 0;
}

static void cdns_pcie_ep_setup_bars(struct cdns_pcie *pcie, int pf)
{
	/* Setup PF BARs */
	cdns_pcie_ep_set_bar(pcie, 0, &epf_bar[0]);

	if (!pcie->sriov_support)
		return;

	/* Setup VF BARs */
	cdns_pcie_ep_set_bar(pcie, 1, &epf_bar[1]);
}

static void cdns_pcie_set_sriov(struct cdns_pcie *pcie, int pf)
{
#if 0
	unsigned int val;

	val =  ccsr_readl(pcie, GPEX_SRIOV_INIT_VFS_TOTAL_VF(pf));
	val &= ~(TTL_VF_MASK << TTL_VF_SHIFT);
	val |= PCIE_VF_NUM << TTL_VF_SHIFT;
	val &= ~(INI_VF_MASK << INI_VF_SHIFT);
	val |= PCIE_VF_NUM << INI_VF_SHIFT;
	ccsr_writel(pcie, GPEX_SRIOV_INIT_VFS_TOTAL_VF(pf), val);

	val =  ccsr_readl(pcie, PCIE_SRIOV_VF_OFFSET_STRIDE);
	val += PCIE_VF_NUM * pf - pf;
	ccsr_writel(pcie, GPEX_SRIOV_VF_OFFSET_STRIDE(pf), val);
#endif
}

static int cdns_pcie_write_header(struct cdns_pcie *pcie, uint fn, struct pci_ep_header *hdr)
{
	cdns_pcie_ep_fn_writew(pcie, fn, PCI_DEVICE_ID, hdr->deviceid);
	cdns_pcie_ep_fn_writeb(pcie, fn, PCI_REVISION_ID, hdr->revid);
	cdns_pcie_ep_fn_writeb(pcie, fn, PCI_CLASS_PROG, hdr->progif_code);
	cdns_pcie_ep_fn_writew(pcie, fn, PCI_CLASS_DEVICE,
			       (hdr->subclass_code | hdr->baseclass_code << 8));
	cdns_pcie_ep_fn_writeb(pcie, fn, PCI_CACHE_LINE_SIZE, hdr->cache_line_size);
	cdns_pcie_ep_fn_writew(pcie, fn, PCI_SUBSYSTEM_ID, hdr->subsys_id);
	cdns_pcie_ep_fn_writeb(pcie, fn, PCI_INTERRUPT_PIN, hdr->interrupt_pin);

	/* Vendor ID can only be modified from function 0, all other functions
	 *  use the same vendor ID as function 0.
	 */
	if (fn == 0) {
		/* Update the vendor IDs. */
		u32 id = CDNS_PCIE_LM_ID_VENDOR(hdr->vendorid) |
			CDNS_PCIE_LM_ID_SUBSYS(hdr->subsys_vendor_id);

		cdns_pcie_writel(pcie, CDNS_PCIE_LM_ID, id);
	}

	return 0;
}

static void cdns_pcie_setup_ep(struct cdns_pcie *pcie)
{
	struct pci_ep_header hdr;
	//const void *fdt = gd->fdt_blob;
	u32 pf, sriov;
	//u32 val;
	int i;
	//int ret = 0;

#if 0
	/* Enable APIO and Memory Win */
	val = ccsr_readl(pcie, PAB_AXI_PIO_CTRL(0));
	val |= APIO_EN | MEM_WIN_EN;
	ccsr_writel(pcie, PAB_AXI_PIO_CTRL(0), val);

	ret = fdt_get_named_resource(pdev, IORESOURCE_MEM, "mem");
	if (ret) {
		dev_err(dev, "missing \"mem\"\n");
		return -EINVAL;
	}
	pcie->mem_res = res;

	ret = fdt_get_named_resource(np, "cdns,max-outbound-regions",
				     &pcie->max_regions);
	if (ret < 0) {
		dev_err(dev, "missing \"cdns,max-outbound-regions\"\n");
		return ret;
	}
	pcie->ob_addr = devm_kcalloc(dev, pcie->max_regions, sizeof(*pcie->ob_addr), GFP_KERNEL);
	if (!pcie->ob_addr)
		return -ENOMEM;
#endif

	sriov = cdns_pcie_readl(pcie, PF_SRIOV_CAPABILITY);
	if (PCI_EXT_CAP_ID(sriov) == PCI_EXT_CAP_ID_SRIOV)
		pcie->sriov_support = 1;

	pf = pcie->sriov_support ? CDNS_PCIE_PF_NUM : 1;

	for (i = 0; i < pf; i++) {
		cdns_pcie_write_header(pcie, pf, &hdr);
		cdns_pcie_ep_setup_bars(pcie, i);
		cdns_pcie_ep_setup_wins(pcie, i);
		if (pcie->sriov_support) {
			cdns_pcie_set_sriov(pcie, i);
		}

	}

	//cdns_pcie_ep_enable_cfg(pcie);
	//cdns_pcie_dump_wins(pcie, pf);
}

static int cdns_pcie_probe(struct udevice *dev)
{
	struct cdns_pcie *pcie = dev_get_priv(dev);
	const void *fdt = gd->fdt_blob;
	int node = dev_of_offset(dev);
	u32 link_ctrl_sta = 0;
	u32 apb_base = 0;
	CDNS_PCIE_LINK_WIDTH negotiated_link_width;
	CDNS_PCIE_LINK_SPEED negotiated_speed;
	u32 val = 0;
	int ret;

	pcie->bus = dev;

	ret = fdt_get_named_resource(fdt, node, "reg", "reg-names",
				     "reg_base", &pcie->reg_res);
	if (ret) {
		printf("cdns_pcie: resource \"reg_base\" not found\n");
		return ret;
	}

	pcie->idx = (pcie->reg_res.start - CDNS_PCIE0_CFG_BASE) / CDNS_PCIE_CFG_SIZE;

	list_add(&pcie->list, &cdns_pcie_list);
#if 0
	pcie->enabled = is_serdes_configured(PCIE_SRDS_PRTCL(pcie->idx));
	if (!pcie->enabled) {
		printf("PCIe%d: %s disabled\n", pcie->idx, dev->name);
		return 0;
	}
#endif
	pcie->reg_base = map_physmem(pcie->reg_res.start,
				     fdt_resource_size(&pcie->reg_res), MAP_NOCACHE);

	apb_base = CDNS_PCIE_CFG_MANGO_APB;
	val = cdns_pcie_readl(pcie,  (apb_base + CDNS_PCIE_IRS_REG0004));
	pcie->mode = (val >> LINK0_MODE_SELECT_BIT) & 0x1;
	if (pcie->mode == CDNS_PCIE_OP_MODE_EP) {
		printf("PCIe%u: %s %s.\n", pcie->idx, dev->name, "Endpoint");
		cdns_pcie_setup_ep(pcie);
	} else {
		printf("PCIe%u: %s %s.\n", pcie->idx, dev->name, "Root Complex");
		pcie->is_rc = 1;
		cdns_pcie_setup_ctrl(pcie);
	}

	if (!cdns_pcie_link_up(pcie)) {
		/* Let the user know there's no PCIe link */
		printf(": no link\n");
		return 0;
	}

	/* Print the negotiated PCIe link width */
	apb_base = CDNS_PCIE_CFG_MANGO_APB;
	link_ctrl_sta = cdns_pcie_readl(pcie, (apb_base + CDNS_PCIE_IRS_REG0080));
	negotiated_link_width = (link_ctrl_sta & LINK0_NEGOTIATED_LINK_WIDTH) >> 19;
	negotiated_speed = (link_ctrl_sta & LINK0_NEGOTIATED_SPEED) >> 16;
	printf(": x%d gen%d\n", negotiated_link_width, negotiated_speed);
	g_pcie = pcie;

	return 0;
}

static const struct dm_pci_ops cdns_pcie_ops = {
	.read_config	= cdns_pcie_read_config,
	.write_config	= cdns_pcie_write_config,
};

static const struct udevice_id cdns_pcie_ids[] = {
	{ .compatible = "sophgo,mango-cdns-pcie" },
	{ }
};

U_BOOT_DRIVER(pcie_sophgo_mango) = {
	.name = "pcie_sophgo_mango",
	.id = UCLASS_PCI,
	.of_match = cdns_pcie_ids,
	.ops = &cdns_pcie_ops,
	.probe	= cdns_pcie_probe,
	.priv_auto = sizeof(struct cdns_pcie),
};
