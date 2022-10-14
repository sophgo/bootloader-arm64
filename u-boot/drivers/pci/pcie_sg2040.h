/****************************************************************************
 * SPDX-License-Identifier: GPL-2.0+
 *
 * Copyright 2021-2025 Sophgo
 *
 * PCIe Gen4 driver for Sophgo Mango SoC
 * Author: lifengchun <fengchun.li@sophgo.com>
 *
 ****************************************************************************/

#ifndef _PCIE_SG2040_H_
#define _PCIE_SG2040_H_
#include <pci.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include "pci_ep.h"

#ifndef CONFIG_SYS_PCI_MEMORY_SIZE
#define CONFIG_SYS_PCI_MEMORY_SIZE		(4 * 1024 * 1024 * 1024ULL)
#endif

#ifndef CONFIG_SYS_PCI_EP_MEMORY_BASE
#define CONFIG_SYS_PCI_EP_MEMORY_BASE   CONFIG_SYS_LOAD_ADDR
#endif

#define CDNS_PCIE0_CFG_BASE         0x60000000
#define CDNS_PCIE1_CFG_BASE         0x62000000
#define CDNS_PCIE2_CFG_BASE         0x64000000
#define CDNS_PCIE3_CFG_BASE         0x66000000
#define CDNS_PCIE_CFG_SIZE          0x02000000
#define CDNS_PCIE0_SLV0_BASE        0x20000000000
#define CDNS_PCIE0_SLV1_BASE        0x22000000000
#define CDNS_PCIE1_SLV0_BASE        0x20000000000
#define CDNS_PCIE1_SLV1_BASE        0x22000000000
#define CDNS_PCIE2_SLV0_BASE        0x20000000000
#define CDNS_PCIE2_SLV1_BASE        0x22000000000
#define CDNS_PCIE3_SLV0_BASE        0x20000000000
#define CDNS_PCIE3_SLV1_BASE        0x22000000000
#define CDNS_PCIE_CFG_LINK0_APB     0x000000
#define CDNS_PCIE_CFG_LINK1_APB     0x800000
#define CDNS_PCIE_CFG_PHY_APB       0x1000000
#define CDNS_PCIE_CFG_MANGO_APB     0x1800000
#define CDNS_PCIE_PF_OFFSET         0x000000
#define CDNS_PCIE_LM_OFFSET         0x100000
#define CDNS_PCIE_RP_OFFSET         0x200000
#define CDNS_PCIE_AXI_OFFSET        0x400000
#define CDNS_PCIE_DMA_OFFSET        0x600000
#define CDNS_PCIE_HAL_MGT_REG       0x040000
#define RCBARPIE                    0x19
#define RC_VENDOR_REG               0x0
#define RC_CLASS_REG                0x8
#define RC_BUS_REG                  0x18
#define RC_IO_LIMIT_REG             0x1c
#define RC_BAR_CONFIG_REG           0x300
#define RC_BAR0_IB_REG              0x800
#define RC_BAR1_IB_REG              0x808
#define RC_NO_BAR_IB_REG            0x810
#define RC_PCIE_CAP_LIST            0xc0
#define PF_SRIOV_CAPABILITY	    0x200
#define CDNS_PCIE_IRS_REG0004       0x0004
#define CDNS_PCIE_IRS_REG0080       0x0080
#define CDNS_PCIE_IRS_REG00C0       0x00C0
#define CDNS_PCIE_IRS_REG0400       0x0400
#define CDNS_PCIE_IRS_REG0404       0x0404
#define CDNS_PCIE_IRS_REG0418       0x0418
#define CDNS_PCIE_IRS_REG041C       0x041C
#define LINK0_MODE_SELECT_BIT                      7
#define LINK0_LTSSM_STATE_MASK          GENMASK(8, 3)
#define LINK0_NEGOTIATED_LINK_WIDTH     GENMASK(21, 19)
#define LINK0_NEGOTIATED_SPEED          GENMASK(18, 16)
#define CDNS_PCIE_LTSSM_L0		0x10 /* L0 state */
#define LM_LOCAL_ERR_STS_REG    0x20c
#define AXI_BAR0_IB_AT_ADDR0    0x800
#define CDNS_PCIE_PF_NUM        1
#define CDNS_PF_BAR_NUM         1
#define CDNS_VF_BAR_NUM         2
#define CDNS_PCIE_BAR_SIZE      (8 * 1024)    /* 8K */
#define CDNS_PCIE_BAR0_SIZE     CDNS_PCIE_BAR_SIZE
#define CDNS_PCIE_BAR1_SIZE     CDNS_PCIE_BAR_SIZE
#define CDNS_PCIE_BAR2_SIZE     CDNS_PCIE_BAR_SIZE
#define CDNS_PCIE_BAR4_SIZE     CDNS_PCIE_BAR_SIZE

/* Root Port Registers (PCI configuration space for the root port function) */
#define CDNS_PCIE_RP_MAX_IB	0x3

/* Region r Outbound AXI to PCIe Address Translation Register 0 */
#define CDNS_PCIE_AT_OB_REGION_PCI_ADDR0(a, r) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x0000 + ((r) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_NBITS_MASK)
#define  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK	GENMASK(19, 12)
#define  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN(devfn) \
	(((devfn) << 12) & CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_DEVFN_MASK)
#define  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK	GENMASK(27, 20)
#define  CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS(bus) \
	(((bus) << 20) & CDNS_PCIE_AT_OB_REGION_PCI_ADDR0_BUS_MASK)

/* Region r Outbound AXI to PCIe Address Translation Register 1 */
#define CDNS_PCIE_AT_OB_REGION_PCI_ADDR1(a, r) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x0004 + ((r) & 0x1f) * 0x0020)

/* Region r Outbound PCIe Descriptor Register 0 */
#define CDNS_PCIE_AT_OB_REGION_DESC0(a, r) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x0008 + ((r) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MASK		GENMASK(3, 0)
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_MEM		0x2
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_IO		0x6
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE0	0xa
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_CONF_TYPE1	0xb
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_NORMAL_MSG	0xc
#define  CDNS_PCIE_AT_OB_REGION_DESC0_TYPE_VENDOR_MSG	0xd
/* Bit 23 MUST be set in RC mode. */
#define  CDNS_PCIE_AT_OB_REGION_DESC0_HARDCODED_RID	BIT(23)
#define  CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK	GENMASK(31, 24)
#define  CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN(devfn) \
	(((devfn) << 24) & CDNS_PCIE_AT_OB_REGION_DESC0_DEVFN_MASK)

/* Region r Outbound PCIe Descriptor Register 1 */
#define CDNS_PCIE_AT_OB_REGION_DESC1(a, r)	\
	((a) + CDNS_PCIE_AXI_OFFSET + 0x000c + ((r) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_REGION_DESC1_BUS_MASK	GENMASK(7, 0)
#define  CDNS_PCIE_AT_OB_REGION_DESC1_BUS(bus) \
	((bus) & CDNS_PCIE_AT_OB_REGION_DESC1_BUS_MASK)

/* Region r AXI Region Base Address Register 0 */
#define CDNS_PCIE_AT_OB_REGION_CPU_ADDR0(a, r) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x0018 + ((r) & 0x1f) * 0x0020)
#define  CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_OB_REGION_CPU_ADDR0_NBITS_MASK)

/* Region r AXI Region Base Address Register 1 */
#define CDNS_PCIE_AT_OB_REGION_CPU_ADDR1(a, r) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x001c + ((r) & 0x1f) * 0x0020)

/* Root Port BAR Inbound PCIe to AXI Address Translation Register */
#define CDNS_PCIE_AT_IB_RP_BAR_ADDR0(a, bar) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x0800 + (bar) * 0x0008)
#define  CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS_MASK	GENMASK(5, 0)
#define  CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS(nbits) \
	(((nbits) - 1) & CDNS_PCIE_AT_IB_RP_BAR_ADDR0_NBITS_MASK)
#define CDNS_PCIE_AT_IB_RP_BAR_ADDR1(a, bar) \
	((a) + CDNS_PCIE_AXI_OFFSET + 0x0804 + (bar) * 0x0008)

/* Vendor ID Register */
#define  CDNS_PCIE_LM_ID		(CDNS_PCIE_LM_OFFSET + 0x0044)
#define  CDNS_PCIE_LM_ID_VENDOR_MASK	GENMASK(15, 0)
#define  CDNS_PCIE_LM_ID_VENDOR_SHIFT	0
#define  CDNS_PCIE_LM_ID_VENDOR(vid) \
	(((vid) << CDNS_PCIE_LM_ID_VENDOR_SHIFT) & CDNS_PCIE_LM_ID_VENDOR_MASK)
#define  CDNS_PCIE_LM_ID_SUBSYS_MASK	GENMASK(31, 16)
#define  CDNS_PCIE_LM_ID_SUBSYS_SHIFT	16
#define  CDNS_PCIE_LM_ID_SUBSYS(sub) \
	(((sub) << CDNS_PCIE_LM_ID_SUBSYS_SHIFT) & CDNS_PCIE_LM_ID_SUBSYS_MASK)

/* Root Complex BAR Configuration Register */
#define  CDNS_PCIE_LM_RC_BAR_CFG	(CDNS_PCIE_LM_OFFSET + 0x0300)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_APERTURE_MASK		GENMASK(5, 0)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_APERTURE(a) \
	(((a) << 0) & CDNS_PCIE_LM_RC_BAR_CFG_BAR0_APERTURE_MASK)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL_MASK			GENMASK(8, 6)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL(c) \
	(((c) << 6) & CDNS_PCIE_LM_RC_BAR_CFG_BAR0_CTRL_MASK)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_APERTURE_MASK		GENMASK(13, 9)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_APERTURE(a) \
	(((a) << 9) & CDNS_PCIE_LM_RC_BAR_CFG_BAR1_APERTURE_MASK)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL_MASK			GENMASK(16, 14)
#define  CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL(c) \
	(((c) << 14) & CDNS_PCIE_LM_RC_BAR_CFG_BAR1_CTRL_MASK)
#define  CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_ENABLE	BIT(17)
#define  CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_32BITS	0
#define  CDNS_PCIE_LM_RC_BAR_CFG_PREFETCH_MEM_64BITS	BIT(18)
#define  CDNS_PCIE_LM_RC_BAR_CFG_IO_ENABLE				BIT(19)
#define  CDNS_PCIE_LM_RC_BAR_CFG_IO_16BITS				0
#define  CDNS_PCIE_LM_RC_BAR_CFG_IO_32BITS				BIT(20)
#define  CDNS_PCIE_LM_RC_BAR_CFG_CHECK_ENABLE			BIT(31)

/* BAR control values applicable to both Endpoint Function and Root Complex */
#define  CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED				0x0
#define  CDNS_PCIE_LM_BAR_CFG_CTRL_IO_32BITS			0x1
#define  CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_32BITS			0x4
#define  CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS	0x5
#define  CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_64BITS			0x6
#define  CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS	0x7

#define LM_RC_BAR_CFG_CTRL_DISABLED(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_DISABLED << (((bar) * 8) + 6))
#define LM_RC_BAR_CFG_CTRL_IO_32BITS(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_IO_32BITS << (((bar) * 8) + 6))
#define LM_RC_BAR_CFG_CTRL_MEM_32BITS(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_32BITS << (((bar) * 8) + 6))
#define LM_RC_BAR_CFG_CTRL_PREF_MEM_32BITS(bar)	\
	(CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_32BITS << (((bar) * 8) + 6))
#define LM_RC_BAR_CFG_CTRL_MEM_64BITS(bar)		\
		(CDNS_PCIE_LM_BAR_CFG_CTRL_MEM_64BITS << (((bar) * 8) + 6))
#define LM_RC_BAR_CFG_CTRL_PREF_MEM_64BITS(bar)	\
	(CDNS_PCIE_LM_BAR_CFG_CTRL_PREFETCH_MEM_64BITS << (((bar) * 8) + 6))
#define LM_RC_BAR_CFG_APERTURE(bar, aperture)		\
					(((aperture) - 2) << ((bar) * 8))
/*
 * Endpoint Function Registers (PCI configuration space for endpoint functions)
 */
#define CDNS_PCIE_EP_FUNC_BASE(fn)	(((fn) << 12) & GENMASK(19, 12))

#define CDNS_PCIE_EP_MIN_APERTURE		128	/* 128 bytes */

/* Endpoint Function BAR Inbound PCIe to AXI Address Translation Register */
#define CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(fn, bar) \
	(CDNS_PCIE_AXI_OFFSET + 0x0840 + (fn) * 0x0040 + (bar) * 0x0008)
#define CDNS_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(fn, bar) \
	(CDNS_PCIE_AXI_OFFSET + 0x0844 + (fn) * 0x0040 + (bar) * 0x0008)

/* Endpoint Bus and Device Number Register */
#define  CDNS_PCIE_LM_EP_ID	(CDNS_PCIE_LM_OFFSET + 0x022c)
#define  CDNS_PCIE_LM_EP_ID_DEV_MASK	GENMASK(4, 0)
#define  CDNS_PCIE_LM_EP_ID_DEV_SHIFT	0
#define  CDNS_PCIE_LM_EP_ID_BUS_MASK	GENMASK(15, 8)
#define  CDNS_PCIE_LM_EP_ID_BUS_SHIFT	8

/* Endpoint Function f BAR b Configuration Registers */
#define CDNS_PCIE_LM_EP_FUNC_BAR_CFG0(fn) \
	(CDNS_PCIE_LM_OFFSET + 0x0240 + (fn) * 0x0008)
#define CDNS_PCIE_LM_EP_FUNC_BAR_CFG1(fn) \
	(CDNS_PCIE_LM_OFFSET + 0x0244 + (fn) * 0x0008)
#define  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) \
	(GENMASK(4, 0) << ((b) * 8))
#define  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE(b, a) \
	(((a) << ((b) * 8)) & CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b))
#define  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b) \
	(GENMASK(7, 5) << ((b) * 8))
#define  CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL(b, c) \
	(((c) << ((b) * 8 + 5)) & CDNS_PCIE_LM_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b))

/* AXI link down register */
#define CDNS_PCIE_AT_LINKDOWN (CDNS_PCIE_AXI_OFFSET + 0x0824)

#define PCI_STD_NUM_BARS	6	/* Number of standard BARs */

/* Boolean true or false */
typedef enum {
	/* Boolean false */
	CDNS_PCIE_FALSE = 0U,
	/* Boolean true */
	CDNS_PCIE_TRUE = 1U
} cdns_pcie_bool;

enum cdns_pcie_rp_bar {
	RP_BAR_UNDEFINED = -1,
	RP_BAR0,
	RP_BAR1,
	RP_NO_BAR
};

typedef enum {
	CDNS_PCIE_ID_0 = 0x0,
	CDNS_PCIE_ID_1,
	CDNS_PCIE_ID_2,
	CDNS_PCIE_ID_3,
	CDNS_PCIE_ID_BUTT
} CDNS_PCIE_ID;

typedef enum {
	CDNS_PCIE_GEN_1 = 0x0,
	CDNS_PCIE_GEN_2,
	CDNS_PCIE_GEN_3,
	CDNS_PCIE_GEN_4,
	CDNS_PCIE_GEN_BUTT
} CDNS_PCIE_GENERATION;

typedef enum {
	CDNS_PCIE_LINK0_X1 = 0x0,
	CDNS_PCIE_LINK0_X2,
	CDNS_PCIE_LINK0_X4,
	CDNS_PCIE_LINK0_X8,
	CDNS_PCIE_LINK0_X16,
	CDNS_PCIE_LINK1_X1,
	CDNS_PCIE_LINK1_X2,
	CDNS_PCIE_LINK1_X4,
	CDNS_PCIE_LINK1_X8,
	CDNS_PCIE_LINK0_X8_LINK1_X8,
	CDNS_PCIE_LANE_MODE_BUTT
} CDNS_PCIE_LANES_MODE;

typedef enum {
	CDNS_PCIE_OP_MODE_EP = 0x0,
	CDNS_PCIE_OP_MODE_RC,
	CDNS_PCIE_OP_MODE_CCIX,
	CDNS_PCIE_OP_MODE_BUTT
} CDNS_PCIE_OP_MODE;

typedef enum {
	CDNS_PCIE_LINK_0 = 0x0,
	CDNS_PCIE_LINK_1,
	CDNS_PCIE_LINK_BUTT
} CDNS_PCIE_LINK_ID;

typedef enum {
	CDNS_PCIE_LINK_NO_RECEIVERS_DETECTED = 0x0,
	CDNS_PCIE_LINK_LINK_TRAINNING_IN_PROGRESS,
	CDNS_PCIE_LINK_DL_INIT_IN_PROGRESS,
	CDNS_PCIE_LINK_DL_INIT_COMPLETED,
	CDNS_PCIE_LINK_STATUS_BUTT
} CDNS_PCIE_LINK_STATUS;

typedef enum {
	CDNS_PCIE_LINK_WIDTH_X1 = 0x0,
	CDNS_PCIE_LINK_WIDTH_X2,
	CDNS_PCIE_LINK_WIDTH_X4,
	CDNS_PCIE_LINK_WIDTH_X8,
	CDNS_PCIE_LINK_WIDTH_X16,
	CDNS_PCIE_LINK_WIDTH_BUTT
} CDNS_PCIE_LINK_WIDTH;

typedef enum {
	CDNS_PCIE_LINK_SPEED_2G5 = 0x0,
	CDNS_PCIE_LINK_SPEED_5G,
	CDNS_PCIE_LINK_SPEED_8G,
	CDNS_PCIE_LINK_SPEED_16G,
	CDNS_PCIE_LINK_SPEED_BUTT
} CDNS_PCIE_LINK_SPEED;

/****************************************************************************
 * The structure that contains transfer configuration data
 ****************************************************************************/
typedef struct {
	uint16_t bus;
	uint16_t dev;
	uint16_t func;
	uint32_t offset;
} transfer_cfg_data;

/****************************************************************************
 * struct cdns_pcie_epf - Structure to hold info about endpoint function
 * @epf_bar: reference to the pci_epf_bar for the six Base Address Registers
 ****************************************************************************/
struct cdns_pcie_epf {
	struct pci_bar *epf_bar[PCI_STD_NUM_BARS];
};

/****************************************************************************
 * struct cdns_pcie - private data for Cadence PCIe controller drivers
 * @reg_base: IO mapped register base
 * @mem_res: start/end offsets in the physical system memory to map PCI accesses
 * @is_rc: tell whether the PCIe controller mode is Root Complex or Endpoint.
 * @bus: In Root Complex mode, the bus number
 * @ops: Platform specific ops to control various inputs from Cadence PCIe
 *       wrapper
 ****************************************************************************/
struct cdns_pcie {
	int idx;
	struct list_head list;
	struct udevice *bus;
	struct fdt_resource reg_res;
	struct fdt_resource cfg_res;
	struct fdt_resource *mem_res;
	void __iomem *cfg_base;
	void __iomem *reg_base;
	bool is_rc;
	u32 vendor_id;
	u32 device_id;
	int phy_count;
	bool enabled;
	int mode;
	int sriov_support;
	u32 max_regions;
	unsigned long ob_region_map;
	phys_addr_t *ob_addr;
	struct phy **phy;
	//struct device_link       **link;
	//const struct cdns_pcie_ops *ops;
	struct  pci_controller hose;
	bool avail_ib_bar[CDNS_PCIE_RP_MAX_IB];
	struct cdns_pcie_epf *epf;
};

struct cdns_pcie_ops {
	int (*start_link)(struct cdns_pcie *pcie);
	void (*stop_link)(struct cdns_pcie *pcie);
	bool (*link_up)(struct cdns_pcie *pcie);
	u64 (*cpu_addr_fixup)(struct cdns_pcie *pcie, u64 cpu_addr);
};

extern struct list_head cdns_pcie_list;

/* The maximum number of regions available when using the AXI Interface */
#define PCIE_MAX_AXI_WRAPPER_REGION_NUM 32U

/* Max ECAM bus number */
#define PCIE_ECAM_MAX_BUS 255U

/* Max ECAM device number */
#define PCIE_ECAM_MAX_DEV 31U

/* Max ECAM function number */
#define PCIE_ECAM_MAX_FUNC 7U

/* Max ECAM offset */
#define PCIE_ECAM_MAX_OFFSET 4095U

/* Max ECAM function number for ARI supported devices. */
#define PCIE_ARI_ECAM_MAX_FUNC 255U

/* Defines the minimum number of address bits passed down from the AXI Interface */
#define PCIE_MIN_AXI_ADDR_BITS_PASSED 8U
#define MAX_AXI_IB_ROOTPORT_REGION_NUM   2

/* ECAM address shift for the Bus number */
#define S_ECAM_B                                       20

/* ECAM address shift for the Device number */
#define S_ECAM_D                                       15

/* ECAM address shift for the Function number */
#define S_ECAM_F                                       12

/* Form the ECAM address */
static inline uintptr_t ECAMADDR(uintptr_t bus, uintptr_t device, uintptr_t function, uintptr_t reg)
{
	return  ((((bus) & 0xffU) << S_ECAM_B) |
		 (((device) & 0x1fU) << S_ECAM_D) |
		 (((function) & 0x7U) << S_ECAM_F) |
		 (((reg) & 0xfffU)));
}

/* Register access */
static inline void cdns_pcie_writeb(struct cdns_pcie *pcie, u32 reg, u8 value)
{
	writeb(value, pcie->reg_base + reg);
}

static inline void cdns_pcie_writew(struct cdns_pcie *pcie, u32 reg, u16 value)
{
	writew(value, pcie->reg_base + reg);
}

static inline void cdns_pcie_writel(struct cdns_pcie *pcie, u32 reg, u32 value)
{
	writel(value, pcie->reg_base + reg);
}

static inline u32 cdns_pcie_readl(struct cdns_pcie *pcie, u32 reg)
{
	return readl(pcie->reg_base + reg);
}

/* Root Port register access */
static inline void cdns_pcie_rp_writeb(struct cdns_pcie *pcie,
				       u32 reg, u8 value)
{
	writeb(value, pcie->reg_base + CDNS_PCIE_RP_OFFSET + reg);
}

static inline void cdns_pcie_rp_writew(struct cdns_pcie *pcie,
				       u32 reg, u16 value)
{
	writew(value, pcie->reg_base + CDNS_PCIE_RP_OFFSET + reg);
}

static inline void cdns_pcie_rp_writel(struct cdns_pcie *pcie,
				       u32 reg, u32 value)
{
	writel(value, pcie->reg_base + CDNS_PCIE_RP_OFFSET + reg);
}

/* Endpoint Function register access */
static inline void cdns_pcie_ep_fn_writeb(struct cdns_pcie *pcie, u8 fn,
					  u32 reg, u8 value)
{
	writeb(value, pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
}

static inline void cdns_pcie_ep_fn_writew(struct cdns_pcie *pcie, u8 fn,
					  u32 reg, u16 value)
{
	writew(value, pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
}

static inline void cdns_pcie_ep_fn_writel(struct cdns_pcie *pcie, u8 fn,
					  u32 reg, u32 value)
{
	writel(value, pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
}

static inline u8 cdns_pcie_ep_fn_readb(struct cdns_pcie *pcie, u8 fn, u32 reg)
{
	return readb(pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
}

static inline u16 cdns_pcie_ep_fn_readw(struct cdns_pcie *pcie, u8 fn, u32 reg)
{
	return readw(pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
}

static inline u32 cdns_pcie_ep_fn_readl(struct cdns_pcie *pcie, u8 fn, u32 reg)
{
	return readl(pcie->reg_base + CDNS_PCIE_EP_FUNC_BASE(fn) + reg);
}

struct cdns_pcie *cdns_get_pcie(void);
#endif /* _PCIE_SG2040_H_ */
