
/*
 * Copyright (c) 2021-2025, Sophgo Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <string.h>
#include <platform_def.h>
#include <arch_helpers.h>
#include <common/bl_common.h>
#include <common/debug.h>
#include <common/desc_image_load.h>
#include <common/fdt_fixup.h>
#include <lib/optee_utils.h>
#include <lib/utils.h>
#include <lib/mmio.h>
#include <plat/common/platform.h>
#include <drivers/delay_timer.h>
#include <drivers/generic_delay_timer.h>
#include <gpio.h>
#include <drivers/sophgo/mango_pcie.h>
#include <drivers/sophgo/mango_pcie_phy.h>

#ifndef CONFIG_ARCH_MANGO_PLD

struct cdns_reg_pairs phy_cfg_ex_SSC[] = {
	{0x0050,  0x8804},
	{0x0062,  0x1B26}
};

struct cdns_reg_pairs phy_cfg_in_SSC[] = {
	{0x0048,  0x000E},
	{0x0049,  0x4006},
	{0x004A,  0x4006},
	{0x004C,  0x0000},

	{0x004F,  0x0000},
	{0x0050,  0x0000},
	{0x0051,  0x0581},
	{0x0052,  0x7F80},

	{0x0053,  0x0041},
	{0x0054,  0x0464},
	{0x0062,  0x0D0D},
	{0x0063,  0x0060}
};

struct cdns_reg_pairs phy_cfg_both_SSC[] = {
	{0x409E,  0x8C67},
	{0x409F,  0x8C67},
	{0x40A0,  0xFF67},
	{0x40A1,  0xFF67},
	{0x40A3,  0xBAA9}
};

struct cdns_reg_pairs phy_cfg_both_SSC_2[] = {
	{0x4081,  0x813E},
	{0x4088,  0x8844},
	{0x4087,  0x884B},
	{0x4086,  0x884B},

	{0x4085,  0x8053},
	{0x4091,  0x033C},
	{0x4097,  0x44CC}
};

struct cdns_reg_pairs phy_cfg_cmn_pllc[] = {
	{0x0046,  0x0000},
	{0x0047,  0x0000},
	{0x004B,  0x0020},
	{0x0045,  0x0019},

	{0x004F,  0x0000},
	{0xC050,  0x0000},
	{0xC0C6,  0x0000},
	{0xC0C7,  0x0000},

	{0xC0CB,  0x0000},
	{0xC0C5,  0x0019},
	{0xC0CF,  0x0000},
	{0xC0D0,  0x0000},

	{0xC002,  0x4010},
	{0xC003,  0x0810},
	{0xC004,  0x0101},
	{0xC006,  0x000A}
};

struct cdns_reg_pairs phy_cfg_mix_reg[] = {
	{0x4020,  0x0041},
	{0x4020,  0x0041},
	{0x4041,  0x0001},
	{0x4042,  0x0001},

	{0x4096,  0x8001},
	{0x40C9,  0xD004},
	{0x4071,  0x0005},
	{0x40B3,  0x000F},

	{0x40B4,  0x0003},
	{0x40C8,  0x0000},
	{0x40CA,  0x0000},
	{0x40D3,  0x000A},

	{0x40F1,  0x0101},
	{0x40F2,  0x0101},
	{0x40F3,  0x0101},
	{0x40F4,  0x0101},

	{0x40F5,  0x0000},
	{0x40F8,  0x0000},
	{0x40F9,  0x0000},
	{0x40FB,  0x0000},

	{0x40FC,  0x0003},
	{0x4110,  0x0101},
	{0x4111,  0x0101},
	{0x4112,  0x0100},

	{0x4124,  0x0000},
	{0x415C,  0x5425},
	{0x4183,  0x745B},
	{0x4184,  0x4B3B},

	{0x4003,  0xE900},
	{0x4003,  0xE900}
};
#endif

#ifdef CONFIG_ARCH_MANGO_PLD
void pcie_udelay(uint32_t cnt)
{
	uint32_t i = 0;
	uint32_t val = 0;

	for (i = 0; i < cnt; i++) {
		val++;
		val = 0;
	}

}
#endif

int pcie_config_bars(PCIE_ID pcie_id, PCIE_LINK_ID link_id, PCIE_OP_MODE op_mode,
		     uint32_t bar0, uint32_t bar1)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (link_id * 0x800000);

	if (op_mode == PCIE_OP_MODE_EP) {
		val = (0b10010) | // BAR0: 32MB aperture
			  (0b100 << 5) | // BAR0: 32bit memory BAR, non prefetchable
			  (0b10010 << 8) | // BAR1: 32MB aperture
			  (0b100 << 13); // BAR1: 32bit memory BAR, non prefetchable
		mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_PF_BAR_CFG_REG_0), val);
		mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_PF_BAR_CFG_REG_1), 0x0);

		// End Point Inbound PCIe to AXI Address Translation
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x840), 0x00000000); // PCIE0_CFG
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x844), 0x200); // PCIE0_CFG
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x848), 0x10000000); // SRAM
	}

	return 0;
}

int pcie_config_link_width(PCIE_ID pcie_id, PCIE_LANES_MODE lanes, PCIE_LINK_WIDTH lk0_width)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	if (lanes == PCIE_LINK0_X16) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
		val &= (~IRS_REG0004_LINK0_LANE_COUNT_IN_MASK);
		val |= (lk0_width << 8); //16 lane
		mmio_write_32((apb_base + PCIE_IRS_REG0004), val);
	} else if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
		val &= (~IRS_REG0004_LINK0_LANE_COUNT_IN_MASK);
		val |= (0x03 << 8); //8 lane
		mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG0178);
		val &= (~IRS_REG0178_LINK1_LANE_COUNT_IN_MASK);
		val |= (0x03 << 24); //8 lane
		mmio_write_32((apb_base + PCIE_IRS_REG0178), val);
	}

	return 0;
}

int pcie_train_link(PCIE_ID pcie_id, PCIE_LANES_MODE lanes)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uint32_t times = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
	val |= (1 << IRS_REG0004_LINK0_LINK_TRAINING_ENABLE_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

	if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0160);
		val |= (1 << IRS_REG0160_LINK1_LINK_TRAINING_ENABLE_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0160), val);
	}

	times = 0;
	do {
#ifdef CONFIG_ARCH_MANGO_PLD
		pcie_udelay(2);
#else
		udelay(2);
#endif
		val = mmio_read_32(apb_base + PCIE_IRS_REG0080);
		val = (val & IRS_REG0080_LINK0_LINK_STATUS_MASK) >> 22;
		times++;
	} while ((val != 0x3) && (times < LTSSM_POLLING_MAX_TIMES));

	NOTICE("%s, Link0 status is %d\n", __func__, val);
	if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		times = 0;
		do {
#ifdef CONFIG_ARCH_MANGO_PLD
			pcie_udelay(2);
#else
			udelay(2);
#endif
			val = mmio_read_32(apb_base + PCIE_IRS_REG0200);
			val = (val & IRS_REG0200_LINK1_LINK_STATUS_MASK) >> 7;
			times++;
		} while ((val != 0x3) && (times < LTSSM_POLLING_MAX_TIMES));

		NOTICE("%s, Link1 status is %d\n", __func__, val);
	}

	return 0;
}

int pcie_link0_reset(PCIE_ID pcie_id)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uint32_t p0x_reset = 0;
	uint32_t reset_x = 0;
	uint32_t linkx_reset_n = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	do {
#ifdef CONFIG_ARCH_MANGO_PLD
		pcie_udelay(2);
#else
		udelay(2);
#endif
		val = mmio_read_32(apb_base + PCIE_IRS_REG03A0);
		p0x_reset = (val >> IRS_REG03A0_PIPE_P00_RESET_N_BIT) & 0x1;
		reset_x = (val >> IRS_REG03A0_PCIE0_RESET_X_FROM_PAD_BIT) & 0x1;
		linkx_reset_n = (val >> IRS_REG03A0_LINK0_RESET_N_BIT) & 0x1;
		NOTICE("%s: PCIE_IRS_REG03A0 = 0x%x\n", __func__, val);
	} while ((p0x_reset != 1) || (reset_x != 1) || (linkx_reset_n != 1));
	val = mmio_read_32(apb_base + PCIE_IRS_REG007C);
	val |= ((uint32_t)1 << IRS_REG007C_REG_LINK0_AXI_RESET_N_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG007C), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG03CC);
	val |= ((uint32_t)1 << IRS_REG03CC_LINK0_MGMT_STICKY_RESET_N_BIT);
	val |= ((uint32_t)1 << IRS_REG03CC_LINK0_MGMT_RESET_N_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG03CC), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
	val |= ((uint32_t)1 << IRS_REG0000_REG_LINK0_PM_RESET_N_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0000), val);

	return 0;
}

int pcie_link1_reset(PCIE_ID pcie_id)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uint32_t p0x_reset = 0;
	uint32_t reset_x = 0;
	uint32_t linkx_reset_n = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	do {
#ifdef CONFIG_ARCH_MANGO_PLD
		pcie_udelay(2);
#else
		udelay(2);
#endif
		val = mmio_read_32(apb_base + PCIE_IRS_REG03A0);
		p0x_reset = (val >> IRS_REG03A0_PIPE_P01_RESET_N_BIT) & 0x1;
		reset_x = (val >> IRS_REG03A0_PCIE1_RESET_X_FROM_PAD_BIT) & 0x1;
		linkx_reset_n = (val >> IRS_REG03A0_LINK1_RESET_N_BIT) & 0x1;
		NOTICE("%s: PCIE_IRS_REG03A0 = 0x%x\n", __func__, val);
	} while ((p0x_reset != 1) || (reset_x != 1) || (linkx_reset_n != 1));

	val = mmio_read_32(apb_base + PCIE_IRS_REG0170);
	val |= ((uint32_t)1 << IRS_REG0170_REG_LINK1_AXI_RESET_N_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0170), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG017C);
	val |= ((uint32_t)1 << IRS_REG017C_LINK1_MGMT_STICKY_RESET_N_BIT);
	val |= ((uint32_t)1 << IRS_REG017C_LINK1_MGMT_RESET_N_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG017C), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0170);
	val |= ((uint32_t)1 << IRS_REG0170_REG_LINK1_PM_RESET_N_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0170), val);

	return 0;
}

int pcie_phy_rst_wait_pclk(PCIE_ID pcie_id)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	val = mmio_read_32(apb_base + PCIE_IRS_REG02F8);
	val |= ((uint32_t)1 << IRS_REG02F8_PHY_RESET_N_BIT_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG02F8), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG01C0);
	val |= ((uint32_t)1 << IRS_REG01C0_REG_PHY_P01_RESET_N);
	val |= ((uint32_t)1 << IRS_REG01C0_REG_PHY_P00_RESET_N);
	mmio_write_32((apb_base + PCIE_IRS_REG01C0), val);

	do {
#ifdef CONFIG_ARCH_MANGO_PLD
		pcie_udelay(2);
#else
		udelay(2);
#endif
		val = mmio_read_32(apb_base + PCIE_IRS_REG0080);
		val = (val & IRS_REG0080_LINK0_CLOCK_STABLE_BIT) >> 31;
		NOTICE("%s, PCIE_IRS_REG0080, val = %d\n", __func__, val);
	} while (val != 0);

	return 0;
}

int pcie_config_phy(PCIE_ID pcie_id, PCIE_LANES_MODE lanes)
{
	uint32_t val = 0;
	uintptr_t base = 0;
#ifndef CONFIG_ARCH_MANGO_PLD
	uint32_t reg = 0;
	uint32_t size = 0;
#ifdef CONFIG_USING_SELF_LIST
	uint32_t cfg_circle = 0;
	uint32_t lane = 0;
#endif
	uint32_t addr = 0;
#endif

	base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	if (lanes == PCIE_LINK0_X16) {
		mmio_write_32(base + PCIE_IRS_REG02F0, 0x00000000);
		mmio_write_32(base + PCIE_IRS_REG02EC, 0x00000000);
	} else if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		mmio_write_32(base + PCIE_IRS_REG02EC, 0x11111111);
	}
	val = mmio_read_32(base + PCIE_IRS_REG03B0);
	val |= (1 << IRS_REG03B0_REG_PHY_APB_RST_BIT) |
	       (1 << IRS_REG03B0_REG_CTRL0_APB_RST_BIT) |
	       (1 << IRS_REG03B0_REG_CTRL1_APB_RST_BIT);
	mmio_write_32(base + PCIE_IRS_REG03B0, val);

#ifndef CONFIG_ARCH_MANGO_PLD
	base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_PHY_APB;
#ifdef CONFIG_USING_SELF_LIST
	for (cfg_circle = 0; cfg_circle < 2; cfg_circle++) {
		size = sizeof(phy_cfg_ex_SSC) / sizeof(struct cdns_reg_pairs);
		for (reg = 0; reg < size; reg++) {
			addr = base + (phy_cfg_ex_SSC[reg].offset << 2);
			mmio_write_32(addr, phy_cfg_ex_SSC[reg].value);
		}

		size = sizeof(phy_cfg_in_SSC) / sizeof(struct cdns_reg_pairs);
		for (reg = 0; reg < size; reg++) {
			addr = base + (phy_cfg_in_SSC[reg].offset << 2);
			mmio_write_32(addr, phy_cfg_in_SSC[reg].value);
		}

		size = sizeof(phy_cfg_both_SSC) / sizeof(struct cdns_reg_pairs);
		for (reg = 0; reg < size; reg++) {
			addr = base + (phy_cfg_both_SSC[reg].offset << 2);
			mmio_write_32(addr, phy_cfg_both_SSC[reg].value);
		}

		size = sizeof(phy_cfg_both_SSC_2) / sizeof(struct cdns_reg_pairs);
		for (lane = 0; lane < 16; lane++) {
			for (reg = 0; reg < size; reg++) {
				addr = base + ((phy_cfg_both_SSC_2[reg].offset << 2) | (lane << 11));
				mmio_write_32(addr, phy_cfg_both_SSC_2[reg].value);
			}
		}

		size = sizeof(phy_cfg_cmn_pllc) / sizeof(struct cdns_reg_pairs);
		for (reg = 0; reg < size; reg++) {
			addr = base + (phy_cfg_cmn_pllc[reg].offset << 2);
			mmio_write_32(addr, phy_cfg_cmn_pllc[reg].value);
		}

		size = sizeof(phy_cfg_mix_reg) / sizeof(struct cdns_reg_pairs);
		for (lane = 0; lane < 16; lane++) {
			for (reg = 0; reg < size; reg++) {
				addr = base + ((phy_cfg_mix_reg[reg].offset << 2) | (lane << 11));
				mmio_write_32(addr, phy_cfg_mix_reg[reg].value);
			}
		}
	}
#else
	size = sizeof(phy_reg_common_cfg_sets) / sizeof(struct cdns_reg_pairs);
	for (reg = 0; reg < size; reg++) {
		addr = base + (phy_reg_common_cfg_sets[reg].offset << 2);
		mmio_write_32(addr, phy_reg_common_cfg_sets[reg].value);
	}

	size = sizeof(phy_reg_port_cfg_sets) / sizeof(struct cdns_reg_pairs);
	for (reg = 0; reg < size; reg++) {
		addr = base + (phy_reg_port_cfg_sets[reg].offset << 2);
		mmio_write_32(addr, phy_reg_port_cfg_sets[reg].value);
	}

	size = sizeof(vga_lut_cfg_sets) / sizeof(struct cdns_reg_pairs);
	for (reg = 0; reg < size; reg++) {
		addr = base + (CDNS_PHY_VGA_LUT_ADDR_REG << 2);
		mmio_write_32(addr, vga_lut_cfg_sets[reg].offset);
		addr = base + (CDNS_PHY_VGA_LUT_DATA_REG << 2);
		mmio_write_32(addr, vga_lut_cfg_sets[reg].value);
	}

	addr = base + (CDNS_PHY_DBG_MUX_CTRL2_REG << 2);
	mmio_write_32(addr, 0x10081840);
	addr = base + (CDNS_PHY_PIPE_FIFO_LATENCY_CTRL_REG << 2);
	mmio_write_32(addr, 0x00000002);
	addr = base + (CNDS_PHY_G3_G4_LNK_EQ_CTRL_REG << 2);
	mmio_write_32(addr, 0x00000001);
	addr = base + (CDNS_PHY_LNK_EQ_CTRL2_REG << 2);
	mmio_write_32(addr, 0x00006C09);

	if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		size = sizeof(phy_reg_port_cfg_sets) / sizeof(struct cdns_reg_pairs);
		for (reg = 0; reg < size; reg++) {
			addr = base + ((phy_reg_port_cfg_sets[reg].offset + 0x200) << 2);
			mmio_write_32(addr, phy_reg_port_cfg_sets[reg].value);
		}

		size = sizeof(vga_lut_cfg_sets) / sizeof(struct cdns_reg_pairs);
		for (reg = 0; reg < size; reg++) {
			addr = base + ((CDNS_PHY_VGA_LUT_ADDR_REG + 0x200) << 2);
			mmio_write_32(addr, vga_lut_cfg_sets[reg].offset);
			addr = base + ((CDNS_PHY_VGA_LUT_DATA_REG + 0x200) << 2);
			mmio_write_32(addr, vga_lut_cfg_sets[reg].value);
		}

		addr = base + (CDNS_PHY_DBG_MUX_CTRL2_REG << 2);
		mmio_write_32(addr, 0x10081840);
		addr = base + (CDNS_PHY_PIPE_FIFO_LATENCY_CTRL_REG << 2);
		mmio_write_32(addr, 0x00000002);
		addr = base + (CNDS_PHY_G3_G4_LNK_EQ_CTRL_REG << 2);
		mmio_write_32(addr, 0x00000001);
		addr = base + (CDNS_PHY_LNK_EQ_CTRL2_REG << 2);
		mmio_write_32(addr, 0x00006C09);
	}
#endif
#endif

	return 0;
}

int pcie_config_ctrl(PCIE_ID pcie_id, PCIE_OP_MODE op_mode,
		     PCIE_LANES_MODE lanes, PCIE_LINK_SPEED speed)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
	if (op_mode == PCIE_OP_MODE_RC) {  //EP is 0, RC is 1
		val |= (1 << IRS_REG0004_LINK0_MODE_SELECT_BIT);
	} else if (op_mode == PCIE_OP_MODE_EP) {
		val &= (~(1 << IRS_REG0004_LINK0_MODE_SELECT_BIT));
	}
	mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0038);
	val &= (~IRS_REG0038_LINK0_PCIE_GENERATION_SEL_MASK);
	val |= ((speed << 14) & IRS_REG0038_LINK0_PCIE_GENERATION_SEL_MASK);
	mmio_write_32((apb_base + PCIE_IRS_REG0038), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
	val &= ~(1 << IRS_REG0004_LINK0_DISABLE_GEN3_DC_BALANCE_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG007C);
	val &= ~(1 << IRS_REG007C_LINK0_PCIE_TARGET_NON_POSTED_REJ_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG007C), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
	val &= ~(1 << IRS_REG0004_LINK0_LINK_TRAINING_ENABLE_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

	if (lanes == PCIE_LINK0_X16) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
		val &= ~(1 << IRS_REG0000_ENABLE_FULL_PIPE_MUX_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0000), val);
	} else if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0178);
		val &= (~IRS_REG0178_LINK1_PCIE_GENERATION_SEL_MASK);
		val |= ((speed << 8) & IRS_REG0178_LINK1_PCIE_GENERATION_SEL_MASK); //Gen4
		if (op_mode == PCIE_OP_MODE_RC) {  //EP is 0, RC is 1
			val |= (1 << IRS_REG0178_LINK1_MODE_SELECT_BIT);
		} else if (op_mode == PCIE_OP_MODE_EP) {
			val &= (~(1 << IRS_REG0178_LINK1_MODE_SELECT_BIT));
		}
		mmio_write_32((apb_base + PCIE_IRS_REG0178), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG0160);
		val &= ~(1 << IRS_REG0160_LINK1_DISABLE_GEN3_DC_BALANCE_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0160), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG0170);
		val &= ~(1 << IRS_REG0170_LINK1_PCIE_TARGET_NON_POSTED_REJ_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0170), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG0160);
		val &= ~(1 << IRS_REG0160_LINK1_LINK_TRAINING_ENABLE_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0160), val);
	}

	return 0;
}

int pcie_init_sideband(PCIE_ID pcie_id, PCIE_LANES_MODE lanes)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
	val |= (1 << IRS_REG0000_PM_CLK_KICK_OFF_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0000), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
	val |= (1 << IRS_REG0004_LINK0_CORE_CLK_SHUTOFF_DETECT_EN_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0160);
	val |= (1 << IRS_REG0160_LINK1_CORE_CLK_SHUTOFF_DETECT_EN_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0160), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
	val |= (1 << IRS_REG0000_ENABLE_FULL_PIPE_MUX_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0000), val);

	mmio_write_32((apb_base + PCIE_IRS_REG02F0), 0x00000000);
	if (lanes == PCIE_LINK0_X16) {
		mmio_write_32((apb_base + PCIE_IRS_REG02EC), 0x00000000);
	} else if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
		val |= (1 << IRS_REG0000_LINK1_CLK_ENABLE_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0000), val);
		mmio_write_32((apb_base + PCIE_IRS_REG02EC), 0x11111111);
	}

	mmio_write_32((apb_base + PCIE_IRS_REG0008), 0x00020001);
	mmio_write_32((apb_base + PCIE_IRS_REG000C), 0x00080004);
	mmio_write_32((apb_base + PCIE_IRS_REG0010), 0x00200010);
	mmio_write_32((apb_base + PCIE_IRS_REG0014), 0x00800040);
	if (lanes == PCIE_LINK0_X16) {
		mmio_write_32((apb_base + PCIE_IRS_REG0018), 0x02000100);
		mmio_write_32((apb_base + PCIE_IRS_REG001C), 0x08000400);
		mmio_write_32((apb_base + PCIE_IRS_REG0020), 0x20001000);
		mmio_write_32((apb_base + PCIE_IRS_REG0024), 0x80004000);
	} else if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		mmio_write_32((apb_base + PCIE_IRS_REG0018), 0x00000000);
		mmio_write_32((apb_base + PCIE_IRS_REG001C), 0x00000000);
		mmio_write_32((apb_base + PCIE_IRS_REG0020), 0x00000000);
		mmio_write_32((apb_base + PCIE_IRS_REG0024), 0x00000000);

		mmio_write_32((apb_base + PCIE_IRS_REG01A0), 0x02000100);
		mmio_write_32((apb_base + PCIE_IRS_REG01A4), 0x08000400);
		mmio_write_32((apb_base + PCIE_IRS_REG01A8), 0x20001000);
		mmio_write_32((apb_base + PCIE_IRS_REG01AC), 0x80004000);
	}

	val = mmio_read_32(apb_base + PCIE_IRS_REG0004);
	val |= (1 << IRS_REG0004_LINK0_CONFIG_ENABLE_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG0004), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0038);
	val &= (~IRS_REG0038_LINK0_MAX_EVAL_ITERATION_MASK) & (~IRS_REG0038_LINK0_SUPPORTED_PRESET_MASK);
	val |= (1 << IRS_REG0038_LINK0_PWR_FAULT_N_BIT) |
		(1 << IRS_REG0038_LINK0_PRSNT_N_BIT) |
		((1 << 4) & IRS_REG0038_LINK0_MAX_EVAL_ITERATION_MASK) |
		((0x7FF << 20) & IRS_REG0038_LINK0_SUPPORTED_PRESET_MASK);
	mmio_write_32((apb_base + PCIE_IRS_REG0038), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
	val &= (~IRS_REG0000_PMA_CMN_REFCLK_DIG_DIV_MASK);
	val |= ((2 << 0) & IRS_REG0000_PMA_CMN_REFCLK_DIG_DIV_MASK);
	mmio_write_32((apb_base + PCIE_IRS_REG0000), val);

	if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG02F8);
		val &= (~IRS_REG02F8_PMA_CMN_REFCLK1_DIG_DIV_MASK);
		val |= ((1 << 29) & IRS_REG02F8_PMA_CMN_REFCLK1_DIG_DIV_MASK);
		mmio_write_32((apb_base + PCIE_IRS_REG02F8), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG0160);
		val |= (1 << IRS_REG0160_LINK1_CONFIG_ENABLE_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG0160), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG01C0);
		val |= (1 << IRS_REG01C0_LINK1_PRSNT_N_BIT) | ((uint32_t)1 << IRS_REG01C0_LINK1_PWR_FAULT_N_BIT);
		mmio_write_32((apb_base + PCIE_IRS_REG01C0), val);

		val = mmio_read_32(apb_base + PCIE_IRS_REG0178);
		val &= (~IRS_REG0178_LINK1_SUPPORTED_PRESET_MASK);
		val |= ((0x7FF << 13) & IRS_REG0178_LINK1_SUPPORTED_PRESET_MASK);
		mmio_write_32((apb_base + PCIE_IRS_REG0178), val);
	}

	return 0;
}

void pcie_set_perst(void)
{
	uint32_t val = 0;

	/* GPIO12 for perst */
	val = gpio_get_direction(MANGO_GPIO12_FOR_PCIE_PERST);
	NOTICE("gpio 12 raw dir = 0x%x\n", val);
	gpio_set_direction(MANGO_GPIO12_FOR_PCIE_PERST, GPIO_DIR_OUT);

	val = gpio_get_value(MANGO_GPIO12_FOR_PCIE_PERST);
	NOTICE("gpio 12 raw level = 0x%x\n", val);
	gpio_set_value(MANGO_GPIO12_FOR_PCIE_PERST, GPIO_LEVEL_HIGH);

#ifdef CONFIG_ARCH_MANGO_PLD
	pcie_udelay(20);
#else
	udelay(20);
#endif
}

int mango_pcie_get_max_payload(PCIE_ID pcie_id, PCIE_LINK_ID link_id,
			       uint32_t func, PCIE_OP_MODE op_mode, PCIE_MAX_PAYLOAD *mps)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uint32_t max_payload = 0;

	if (func > 7)
		return -1;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + (link_id * 0x800000)
		   + PCIE_CFG_LINK0_APB + (func * 0x1000);
	if (op_mode == PCIE_OP_MODE_RC) {
		val = mmio_read_32(apb_base + PCIE_RP_OFFSET + LINKX_RP_DEV_CTRL_AND_STS_REG);
		max_payload = (val & LINKX_DEV_CTRL_AND_STS_MPS_MASK) >> 5;
		*mps = (PCIE_MAX_PAYLOAD)max_payload;
		NOTICE("PCIe RC max payload %d\n", max_payload);
	} else {
		val = mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_DEV_CTRL_AND_STS_REG);
		max_payload = (val & LINKX_DEV_CTRL_AND_STS_MPS_MASK) >> 5;
		*mps = (PCIE_MAX_PAYLOAD)max_payload;
		NOTICE("PCIe EP max payload %d\n", max_payload);
	}

	return 0;
}

int mango_pcie_set_max_payload(PCIE_ID pcie_id, PCIE_LINK_ID link_id,
			       uint32_t func, PCIE_OP_MODE op_mode, PCIE_MAX_PAYLOAD mps)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	if (func > 7)
		return -1;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + (link_id * 0x800000)
		   + PCIE_CFG_LINK0_APB + (func * 0x1000);
	if (op_mode == PCIE_OP_MODE_RC) {
		val = mmio_read_32(apb_base + PCIE_RP_OFFSET + LINKX_RP_DEV_CTRL_AND_STS_REG);
		val &= (~LINKX_DEV_CTRL_AND_STS_MPS_MASK);
		val |= ((mps << 5) &  LINKX_DEV_CTRL_AND_STS_MPS_MASK);
		mmio_write_32((apb_base + PCIE_RP_OFFSET + LINKX_RP_DEV_CTRL_AND_STS_REG), val);
		NOTICE("set PCIe RC max payload %d\n", mps);
	} else {
		val = mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_DEV_CTRL_AND_STS_REG);
		val &= (~LINKX_DEV_CTRL_AND_STS_MPS_MASK);
		val |= ((mps << 5) &  LINKX_DEV_CTRL_AND_STS_MPS_MASK);
		mmio_write_32((apb_base + PCIE_PF_OFFSET + LINKX_PF_DEV_CTRL_AND_STS_REG), val);
		NOTICE("set PCIe EP max payload %d\n", mps);
	}

	return 0;
}

int mango_pcie_set_max_read_req_size(PCIE_ID pcie_id, PCIE_LINK_ID link_id,
				     uint32_t func, PCIE_OP_MODE op_mode, PCIE_MAX_READ_REQ_SIZE mrrs)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;

	if (func > 7)
		return -1;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + (link_id * 0x800000)
		   + PCIE_CFG_LINK0_APB + (func * 0x1000);
	if (op_mode == PCIE_OP_MODE_RC) {
		val = mmio_read_32(apb_base + PCIE_RP_OFFSET + LINKX_RP_DEV_CTRL_AND_STS_REG);
		val &= (~LINKX_DEV_CTRL_AND_STS_MRRS_MASK);
		val |= ((mrrs << 5) &  LINKX_DEV_CTRL_AND_STS_MRRS_MASK);
		mmio_write_32((apb_base + PCIE_RP_OFFSET + LINKX_RP_DEV_CTRL_AND_STS_REG), val);
		NOTICE("set PCIe RC max read req size %d\n", mrrs);
	} else {
		val = mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_DEV_CTRL_AND_STS_REG);
		val &= (~LINKX_DEV_CTRL_AND_STS_MRRS_MASK);
		val |= ((mrrs << 5) &  LINKX_DEV_CTRL_AND_STS_MRRS_MASK);
		mmio_write_32((apb_base + PCIE_PF_OFFSET + LINKX_PF_DEV_CTRL_AND_STS_REG), val);
		NOTICE("set PCIe EP max read req size %d\n", mrrs);
	}

	return 0;
}

void mango_pcie_init(PCIE_ID pcie_id, PCIE_OP_MODE op_mode,
		     PCIE_LANES_MODE lanes, PCIE_LINK_SPEED speed)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uint32_t ltssm_state = 0;
	PCIE_LINK_STATUS link_status = 0;
	PCIE_LINK_WIDTH negotiated_link_width = 0;
	PCIE_LINK_SPEED negotiated_speed = 0;
	uint32_t max_payload = 0;
	uint32_t bar0 = 0;
	uint32_t bar1 = 0;

	NOTICE("PCIe init, op_mode = %d\n", op_mode);
	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	mmio_write_32((apb_base + PCIE_IRS_REG0844), 0x0);
	mmio_write_32((apb_base + PCIE_IRS_REG0848), 0x0);
	mmio_write_32((apb_base + PCIE_IRS_REG084C), 0x0);
	mmio_write_32((apb_base + PCIE_IRS_REG0850), 0x0);
	pcie_init_sideband(pcie_id, lanes);
	pcie_config_ctrl(pcie_id, op_mode, lanes, speed);
	pcie_config_phy(pcie_id, lanes);
	pcie_phy_rst_wait_pclk(pcie_id);

	pcie_config_link_width(pcie_id, lanes, PCIE_LINK_WIDTH_X16);

	if (op_mode == PCIE_OP_MODE_RC) {
		pcie_set_perst();
	}

	if (lanes == PCIE_LINK0_X16) {
		pcie_link0_reset(pcie_id);
	}
	if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		pcie_link0_reset(pcie_id);
		pcie_link1_reset(pcie_id);
	}
	pcie_train_link(pcie_id, lanes);

	if (lanes == PCIE_LINK0_X16) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG00C0);
		ltssm_state = (val & IRS_REG00C0_LINK0_LTSSM_STATE_MASK) >> 3;
		val = mmio_read_32(apb_base + PCIE_IRS_REG0080);
		link_status = (val & IRS_REG0080_LINK0_LINK_STATUS_MASK) >> 22;
		negotiated_link_width = (val & IRS_REG0080_LINK0_NEGOTIATED_LINK_WIDTH) >> 19;
		negotiated_speed = (val & IRS_REG0080_LINK0_NEGOTIATED_SPEED) >> 16;

		if ((ltssm_state != 0x10) || (link_status != PCIE_LINK_DL_INIT_COMPLETED) ||
		    (speed != negotiated_speed)) {
			ERROR("PCIe EP x16 not linked\n");
		}
	}

	if (lanes == PCIE_LINK0_X8_LINK1_X8) {
		val = mmio_read_32(apb_base + PCIE_IRS_REG0204);
		ltssm_state = (val & IRS_REG0204_LINK1_LTSSM_STATE_MASK) >> 3;
		val = mmio_read_32(apb_base + PCIE_IRS_REG0200);
		link_status = (val & IRS_REG0200_LINK1_LINK_STATUS_MASK) >> 7;
		negotiated_link_width = (val & IRS_REG0200_LINK1_NEGOTIATED_LINK_WIDTH) >> 0;
		val = mmio_read_32(apb_base + PCIE_IRS_REG0208);
		negotiated_speed = (val & IRS_REG0208_LINK1_NEGOTIATED_SPEED) >> 0;

		if ((ltssm_state != 0x10) || (link_status != PCIE_LINK_DL_INIT_COMPLETED) ||
		    (speed != negotiated_speed)) {
			ERROR("PCIe EP x8 not linked\n");
		}
	}

	NOTICE("PCIe init, %d - %d - %d -%d\n", ltssm_state, link_status, negotiated_link_width, negotiated_speed);
	pcie_config_bars(pcie_id, PCIE_LINK_0, op_mode, bar0, bar1);

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB;
	if (op_mode == PCIE_OP_MODE_RC) {
		val = mmio_read_32(apb_base + PCIE_RP_OFFSET + LINKX_RP_DEV_CAP_REG);
		max_payload = (val & LINKX_DEV_CAP_MAX_PL_MASK);
		NOTICE("PCIe RC max payload %d\n", max_payload);
	} else {
		mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_PF_PHY_FUNC_CFG_REG), 0x01);
		val = mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_DEV_CAP_REG);
		max_payload = (val & LINKX_DEV_CAP_MAX_PL_MASK);
		NOTICE("PCIe EP max payload %d\n", max_payload);
	}
}

int pcie_write_msi(PCIE_ID pcie_id, PCIE_LINK_ID link_id)
{
	uintptr_t apb_base = 0;
	uint32_t msi_addr_l = 0;
	uint32_t msi_addr_h = 0;
	uint32_t msi_data = 0;

	//pcie addr mapping
	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;
	mmio_write_32((apb_base + PCIE_IRS_REG0400), 0x00000000);
	mmio_write_32((apb_base + PCIE_IRS_REG0404), 0x200);
	mmio_write_32((apb_base + PCIE_IRS_REG0418), 0x01ffffff);
	mmio_write_32((apb_base + PCIE_IRS_REG041C), 0x200);

	//read msi addr and date
	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (link_id * 0x800000);
	msi_addr_l = mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_MSI_ADDR_L_REG);
	msi_addr_h = mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_MSI_ADDR_H_REG);
	msi_data =  mmio_read_32(apb_base + PCIE_PF_OFFSET + LINKX_PF_MSI_DATA_REG);

	//OB region map
	mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_AT_REG_0), ((msi_addr_l & 0xFE000000) + 0x18));
	mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_AT_REG_1), msi_addr_h);
	mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_DSPT_REG_0), 0x00002); //memory write
	mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_AXI_RGN_ADDR_REG_0), (0x00000000 + 0x18));
	mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_AXI_RGN_ADDR_REG_1), 0x200);

	//write msi
	mmio_write_32(0x30010098, 0x404);
	NOTICE("PCIe write msi, addr:%x, data:%x\n", msi_addr_l, msi_data);
	mmio_write_32((0x8000000000 | (msi_addr_l & 0x1FFFFFF)), msi_data);

	NOTICE("PCIe write msi, finished\n");

	return 0;
}

void mango_ccix_init(PCIE_ID pcie_id, PCIE_OP_MODE op_mode, PCIE_LINK_SPEED speed)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uint32_t ltssm_state = 0;
	PCIE_LINK_STATUS link_status = 0;
	PCIE_LINK_WIDTH negotiated_link_width = 0;
	PCIE_LINK_SPEED negotiated_speed = 0;

	NOTICE("CCIX init, pcie id = %d, op_mode = %d\n", pcie_id, op_mode);
	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	pcie_init_sideband(pcie_id, PCIE_LINK0_X16);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0000);
	val |= 1 << IRS_REG0000_LINK0_BYPASS_RMT_TX_EQ;
	mmio_write_32((apb_base + PCIE_IRS_REG0000), val);
	val = mmio_read_32(apb_base + PCIE_IRS_REG0038);
	val &= (~IRS_REG0038_LINK0_MAX_EVAL_ITERATION_MASK);
	mmio_write_32((apb_base + PCIE_IRS_REG0038), val);

	pcie_config_ctrl(pcie_id, op_mode, PCIE_LINK0_X16, speed);
	pcie_config_phy(pcie_id, PCIE_LINK0_X16);
	pcie_phy_rst_wait_pclk(pcie_id);
	pcie_config_link_width(pcie_id, PCIE_LINK0_X16, PCIE_LINK_WIDTH_X16);

	pcie_set_perst();
	pcie_link0_reset(pcie_id);
	pcie_link1_reset(pcie_id);

	pcie_train_link(pcie_id, PCIE_LINK0_X16);

	do {
		val = mmio_read_32(apb_base + PCIE_IRS_REG00C0);
		ltssm_state = (val & IRS_REG00C0_LINK0_LTSSM_STATE_MASK) >> 3;
		val = mmio_read_32(apb_base + PCIE_IRS_REG0080);
		link_status = (val & IRS_REG0080_LINK0_LINK_STATUS_MASK) >> 22;
		negotiated_link_width = (val & IRS_REG0080_LINK0_NEGOTIATED_LINK_WIDTH) >> 19;
		negotiated_speed = (val & IRS_REG0080_LINK0_NEGOTIATED_SPEED) >> 16;

	} while	((ltssm_state != 0x10) || (link_status != PCIE_LINK_DL_INIT_COMPLETED) ||
		 (negotiated_speed != speed) || (negotiated_link_width != PCIE_LINK_WIDTH_X16));

	NOTICE("CCIX init, %d - %d - %d -%d\n", ltssm_state, link_status, negotiated_link_width, negotiated_speed);

	val = mmio_read_32(apb_base + PCIE_IRS_REG0858);
	val = val & 0x00FFFFFF;
	val = val & (~(IRS_REG0858_CCIX_BUS_NUM_MASK));
	if (op_mode == PCIE_OP_MODE_RC) {
		val = val | 0x00;
	} else if (op_mode == PCIE_OP_MODE_EP) {
		val = val | 0x13;
	}
	mmio_write_32((apb_base + PCIE_IRS_REG0858), val);

	val = mmio_read_32(apb_base + PCIE_IRS_REG007C);
	val = val | (1 << IRS_REG007C_LINK0_VC_COUNT_BIT);
	mmio_write_32((apb_base + PCIE_IRS_REG007C), val);

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB;
	//val = mmio_read_32(apb_base + PCIE_LM_OFFSET + LINKX_LM_CCIX_CTRL_REG);
	//val = val & (~ (LINK0_LM_CCIX_CTRL_VENDOR_ID_MASK));
	//val = val | 0x17cd;
	//mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_CCIX_CTRL_REG), val);

	if (op_mode == PCIE_OP_MODE_EP) {
		val = 0;
		val = val | ((uint32_t)1 << LINK0_VC_RES_CTRL_VC_ENABLE_BIT);
		val = val | (1 << LINK0_VC_RES_CTRL_TC_VC_MAP_BIT);
		mmio_write_32((apb_base + PCIE_PF_OFFSET + LINKX_PF_VC_RES_CTRL_REG_0), val);

		val = 0;
		val = val | ((uint32_t)1 << LINK0_VC_RES_CTRL_VC_ENABLE_BIT);
		val = val | (0x100 << 16);
		val = val | (1 << 1);
		val = val | (1 << LINK0_VC_RES_CTRL_TC_VC_MAP_BIT);
		mmio_write_32((apb_base + PCIE_PF_OFFSET + LINKX_PF_VC_RES_CTRL_REG_1), val);
	} else if (op_mode == PCIE_OP_MODE_RC) {
		val = 0;
		val = val | ((uint32_t)1 << LINK0_VC_RES_CTRL_VC_ENABLE_BIT);
		val = val | (1 << LINK0_VC_RES_CTRL_TC_VC_MAP_BIT);
		mmio_write_32((apb_base + PCIE_RP_OFFSET + LINKX_RP_VC_RES_CTRL_REG_0), val);

		val = 0;
		val = val | ((uint32_t)1 << LINK0_VC_RES_CTRL_VC_ENABLE_BIT);
		val = val | (0x100 << 16);
		val = val | (1 << 1);
		val = val | (1 << LINK0_VC_RES_CTRL_TC_VC_MAP_BIT);
		mmio_write_32((apb_base + PCIE_RP_OFFSET + LINKX_RP_VC_RES_CTRL_REG_1), val);
	}

	NOTICE("CCIX init vc map cfg done\n");
	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_MANGO_APB;

	//do {
		val = mmio_read_32(apb_base + PCIE_IRS_REG00F8);
	//	val = (val >> IRS_RGE00F8_CCIX_VC_ENABLE_BIT) & 0x01;
	//} while (val != 0x1);

	NOTICE("CCIX init vc enable, val = 0x%x\n", val);
}

int pcie_udma_axi_pcie_map(PCIE_ID pcie_id, PCIE_LINK_ID link_id, PCIE_OP_MODE op_mode)
{
	uint32_t val = 0;
	uintptr_t apb_base = 0;
	uintptr_t dst = 0;

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000);

	NOTICE("%s: 1\n", __func__);
	//pcie addr mapping
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG0400), 0x00000000);
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG0404), (0x40 + pcie_id * 4));
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG0418), 0xffffffff);
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG041C), (0x43 + pcie_id * 4));

	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG0408), 0x00000000);
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG040C), (0x44 + pcie_id * 4));
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG0420), 0xffffffff);
	mmio_write_32((apb_base + PCIE_CFG_MANGO_APB + PCIE_IRS_REG0424), (0x47 + pcie_id * 4));

	NOTICE("%s: 2\n", __func__);

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (link_id * 0x800000);
	if (op_mode == PCIE_OP_MODE_EP) {
		val = (0b01101) | // BAR0: 1MB aperture
			  (0b110 << 5) | // BAR0: 64bit memory BAR, non prefetchable
			  (0b00000 << 8) | // BAR1: 0MB aperture
			  (0b000 << 13) | // BAR1: disable
			  (0b10100 << 16) | // BAR2: 128M aperture
			  (0b110 << 21); // BAR2: 64Bit memory BAR, non prefetchable

		mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_PF_BAR_CFG_REG_0), val);
		mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_PF_BAR_CFG_REG_1), 0x0);

		val = mmio_read_32(apb_base + 0x4);
		val |= 0x2;
		mmio_write_32((apb_base + 0x4), val);

		mmio_read_32(apb_base + 0x10);
		mmio_write_32((apb_base + 0x10), 0x100000);
		mmio_read_32(apb_base + 0x14);
		mmio_write_32((apb_base + 0x14), 0x0);

		mmio_read_32(apb_base + 0x18);
		mmio_write_32((apb_base + 0x18), 0x00000000);
		mmio_read_32(apb_base + 0x1c);
		mmio_write_32((apb_base + 0x1c), 0x80);

		NOTICE("%s: 3\n", __func__);
		// End Point Inbound PCIe to AXI Address Translation
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x840), 0x62000000); // PCIE0_CFG
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x844), 0x70); // PCIE0_CFG
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x850), 0x00000000); // SRAM
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x854), 0x80); // SRAM
	} else if (op_mode == PCIE_OP_MODE_RC) {
		mmio_write_32((apb_base + PCIE_LM_OFFSET + LINKX_LM_RC_BAR_CFG_REG), 0x1E0000);

		//mmio_read_32(0x4000100010);
		//mmio_write_32(0x4000100010, 0x100000);
		//mmio_read_32(0x4000100014);
		//mmio_write_32(0x4000100014, 0x0);

		//mmio_read_32(0x4000100018);
		//mmio_write_32(0x4000100018, 0x40000000);
		//mmio_read_32(0x400010001c);
		//mmio_write_32(0x400010001c, 0x80);
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x810), 47);
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + 0x814), 0);

		NOTICE("%s: 4\n", __func__);
		//OB region map
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_AT_REG_0), (100000 + 0x13));
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_AT_REG_1), 0);
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_DSPT_REG_0), 0x80000a); //memory write
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_AXI_RGN_ADDR_REG_0), (0x00000000 + 0x13));
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_AXI_RGN_ADDR_REG_1),
			      (0x40 + (link_id * 4) + (pcie_id * 8)));

		dst = 0x8000000000;
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_AT_REG_0 + 0x20),
			      ((dst & 0xFE000000) + 0x1a));
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_AT_REG_1 + 0x20),
			      ((dst >> 32) & 0xffffffff));
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_OB_DSPT_REG_0 + 0x20),
			      0x800002); //memory write
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_AXI_RGN_ADDR_REG_0 + 0x20),
			      (0x02000000 + 0x1a));
		mmio_write_32((apb_base + PCIE_AXI_OFFSET + LINKX_AXI_R0_AXI_RGN_ADDR_REG_1 + 0x20),
			      (0x40 + (link_id * 4) + (pcie_id * 8)));

	}

	NOTICE("%s: 5\n", __func__);
	return 0;
}

int pcie_udma_test(PCIE_ID pcie_id, PCIE_OP_MODE op_mode, PCIE_TD_DIRECTION dir)
{
	uintptr_t apb_base = 0;
	uintptr_t apb_base1 = 0;
	uint32_t val = 0;
	uint32_t val1 = 0;
	uint32_t int_done = 0;
	uint32_t int_err = 0;
	uint32_t addr = 0;
	uint32_t *dma_test_buff = (uint32_t *)0x8000000000;
	uint32_t *dma_chip0_buff = (uint32_t *)0x40000000;
	uint32_t *dma_chip0_buff_1 = (uint32_t *)0x141000000;
	PCIE_XD_DESC *desc = (PCIE_XD_DESC *)0x8000000000;
	uint32_t size = 0x1000000;
	uint32_t it = 0;
	uint32_t function = 0;
	uint64_t time = 0;
	uint64_t time1 = 0;
	uint64_t band_width = 0;
	uint64_t band_width1 = 0;

	NOTICE("%s: 1\n", __func__);

	if ((pcie_id == 0x1) && (dir == PCIE_OUTB_DIR)) {
		for (it = 0; it < 0x100; it++) {
			//memset((void *)((uint8_t *)dma_test_buff + (it << 12)), 0x5a, 0x1000);
		}
	} else if ((pcie_id == 0) && (dir == PCIE_INB_DIR)) {
		for (it = 0; it < 0x100; it++) {
			memset((void *)((uint8_t *)dma_chip0_buff + (it << 12)), 0x5a, 0x1000);
		}

		for (it = 0; it < 0x100; it++) {
			memset((void *)((uint8_t *)dma_chip0_buff_1 + (it << 12)), 0x5a, 0x1000);
		}
	}

	NOTICE("%s: 2\n", __func__);

	for (function = 0; function < 8; function++) {
		mango_pcie_set_max_payload(pcie_id, 0, function, op_mode, 0);
		mango_pcie_set_max_read_req_size(pcie_id, 0, function, op_mode, 0);
		mango_pcie_set_max_payload(pcie_id, 1, function, op_mode, 0);
		mango_pcie_set_max_read_req_size(pcie_id, 1, function, op_mode, 0);
	}

	if (op_mode == PCIE_OP_MODE_EP) {
		if (dir == 0) {
			pcie_udma_axi_pcie_map(pcie_id, PCIE_LINK_0, op_mode);
			NOTICE("pcie[%d]: link0, EP, dst addr is %p, val = 0x%x\n", pcie_id, dma_test_buff, val);

			pcie_udma_axi_pcie_map(pcie_id, PCIE_LINK_1, op_mode);
			NOTICE("pcie[%d]: link1, EP, dst addr is %p, val = 0x%x\n", pcie_id, dma_test_buff, val);
			return 0;
		}
		NOTICE("pcie[%d]: EP, dst addr is %p, val = 0x%x\n", pcie_id, dma_test_buff, val);
		//return 0;
	} else if (op_mode == PCIE_OP_MODE_RC) {
		pcie_udma_axi_pcie_map(pcie_id, PCIE_LINK_0, op_mode);
		pcie_udma_axi_pcie_map(pcie_id, PCIE_LINK_1, op_mode);

		NOTICE("%s: 3.1\n", __func__);
		if (dir == 0) {
			dma_test_buff = (uint32_t *)0x4002000000;
			for (it = 0; it < 0x100; it++) {
				memset((void *)((uint8_t *)dma_test_buff + (it << 12)), 0x5a, 0x1000);
			}

			dma_test_buff = (uint32_t *)0x4402000000;
			for (it = 0; it < 0x100; it++) {
				memset((void *)((uint8_t *)dma_test_buff + (it << 12)), 0x5a, 0x1000);
			}
		}
		dma_test_buff = (uint32_t *)0x8000000000;

		NOTICE("%s: 3.2\n", __func__);
		desc = (PCIE_XD_DESC *)0x4002000000;
		memset((void *)desc, 0x00, sizeof(PCIE_XD_DESC));
		desc->sys_lo_addr = ((uintptr_t)dma_test_buff) & 0xffffffff;
		desc->sys_hi_addr = (((uintptr_t)dma_test_buff) >> 32) & 0xffffffff;
		desc->ext_lo_addr = ((uintptr_t)dma_chip0_buff) & 0xffffffff;
		desc->ext_hi_addr = (((uintptr_t)dma_chip0_buff) >> 32) & 0xffffffff;
		desc->size_and_ctrl.ctrl_bits.control_bits = 0x01;
		desc->size_and_ctrl.size = size;

		NOTICE("%s: 3.3\n", __func__);
		val = mmio_read_32((uintptr_t)dma_test_buff);
		NOTICE("pcie[%d]: link0 RC, dst addr is %p, val = 0x%x\n", pcie_id, dma_test_buff, val);
		val = mmio_read_32(0x4002001000);
		NOTICE("pcie[%d]: link0 RC, src init val = 0x%x\n", pcie_id, val);

		NOTICE("%s: 3.4\n", __func__);
		desc = (PCIE_XD_DESC *)0x4402000000;
		memset((void *)desc, 0x00, sizeof(PCIE_XD_DESC));
		desc->sys_lo_addr = ((uintptr_t)dma_test_buff) & 0xffffffff;
		desc->sys_hi_addr = (((uintptr_t)dma_test_buff) >> 32) & 0xffffffff;
		desc->ext_lo_addr = ((uintptr_t)dma_chip0_buff_1) & 0xffffffff;
		desc->ext_hi_addr = (((uintptr_t)dma_chip0_buff_1) >> 32) & 0xffffffff;
		desc->size_and_ctrl.ctrl_bits.control_bits = 0x01;
		desc->size_and_ctrl.size = size;

		NOTICE("%s: 3.5\n", __func__);
		val = mmio_read_32((uintptr_t)dma_test_buff);
		NOTICE("pcie[%d]: link1 RC, dst addr is %p, val = 0x%x\n", pcie_id, dma_test_buff, val);
		val = mmio_read_32(0x4402001000);
		NOTICE("pcie[%d]: link1 RC, src init val = 0x%x\n", pcie_id, val);

		return 0;

	} else {
		NOTICE("op mode is invalid!\n");
		return -1;
	}

	//config dma controller registers link0 dma
	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (PCIE_LINK_0 * 0x800000);
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_INT_EN_REG), 0x1);
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_INT_DIS_REG), 0x0);

	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_ATTR_LO_REG), 0x0);
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_ATTR_HI_REG), 0x0);

	desc = (PCIE_XD_DESC *)0x8000000000;
	addr = ((uintptr_t)(desc)) & 0xffffffff;
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_SP_LO_REG), addr);
	addr = (((uintptr_t)(desc)) >> 32) & 0xffffffff;
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_SP_HI_REG), addr);

	NOTICE("%s: 5, link0 dma cfg!\n", __func__);

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (PCIE_LINK_1 * 0x800000);
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_INT_EN_REG), 0x1);
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_INT_DIS_REG), 0x0);

	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_ATTR_LO_REG), 0x0);
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_ATTR_HI_REG), 0x0);

	desc = (PCIE_XD_DESC *)0x8000000000;
	addr = ((uintptr_t)(desc)) & 0xffffffff;
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_SP_LO_REG), addr);
	addr = (((uintptr_t)(desc)) >> 32) & 0xffffffff;
	mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_SP_HI_REG), addr);

	NOTICE("%s: 5, link1 dma cfg!\n", __func__);

	apb_base = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (PCIE_LINK_0 * 0x800000);
	apb_base1 = PCIE0_CFG_BASE + (pcie_id * 0x02000000) + PCIE_CFG_LINK0_APB + (PCIE_LINK_1 * 0x800000);

	time = read_cntpct_el0();

	if (dir == PCIE_OUTB_DIR) {
		mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_CTRL_REG), 0x3);
	} else if (dir == PCIE_INB_DIR) {
		mmio_write_32((apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_CTRL_REG), 0x1);
	} else {
		NOTICE("PCIe dma test, direction is invalid.\n");
		return -1;
	}

	time1 = read_cntpct_el0();

	if (dir == PCIE_OUTB_DIR) {
		mmio_write_32((apb_base1 + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_CTRL_REG), 0x3);
	} else if (dir == PCIE_INB_DIR) {
		mmio_write_32((apb_base1 + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_CHN0_CTRL_REG), 0x1);
	} else {
		NOTICE("PCIe dma test, direction is invalid.\n");
		return -1;
	}

	NOTICE("%s: 6\n", __func__);

	do {
		val = mmio_read_32(apb_base + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_INT_REG);
		int_done = val & 0x1;
		int_err = (val >> 8) & 0x1;
	} while ((!int_done) && (!int_err));

	time = read_cntpct_el0() - time;
	band_width = size * read_cntfrq_el0() / time;

	do {
		val1 = mmio_read_32(apb_base1 + PCIE_DMA_OFFSET + LINKX_PCIE_DMA_INT_REG);
		int_done = val1 & 0x1;
		int_err = (val1 >> 8) & 0x1;
	} while ((!int_done) && (!int_err));

	time1 = read_cntpct_el0() - time1;
	band_width1 = size * read_cntfrq_el0() / time1;

	NOTICE("PCIe dma test, link0 finished!, int = 0x%x, band width = %ld B/s.\n", val, band_width);
	NOTICE("PCIe dma test, link1 finished!, int = 0x%x, band width = %ld B/s.\n", val1, band_width1);

	return 0;
}

