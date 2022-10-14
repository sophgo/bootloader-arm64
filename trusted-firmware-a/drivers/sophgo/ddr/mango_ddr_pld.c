/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <string.h>
#include <platform_def.h>
#include <drivers/delay_timer.h>
#include <common/debug.h>
#include <lib/mmio.h>
#include <platform_def.h>
#include <drivers/sophgo/mango_ddr_reg_pld.h>
#include <drivers/sophgo/mango_ddr.h>

#define DRAM_BSTLEN 0x3
#define DRAM_BSTLEN_BIT_OFFSET  0x8
#define DRAM_BSTLEN_BIT_MASK  0x7

#define MANGO_DDRC_BASE	DDR0_CFG_BASE
#define MANGO_DDRC_SIZE	DDR0_CFG_SIZE
#define MANGO_DDRC_MAX	4

/* Initialize DDR */
static uint32_t ddr_init_pld(uint64_t ddr_cfg_base_addr)
{
	int i;
	unsigned int wdata, rdata;

	for (i = 0; i <= 430; i++) {
		wdata = DENALI_CTL_DATA(i);
		mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(i)), wdata);
	}

	for (i = 0; i <= 203; i++) {
		wdata = DENALI_PI_DATA(i);
		mmio_write_32((ddr_cfg_base_addr + DENALI_PI_REG(i)), wdata);
	}

	for (i = 0; i <= 2449; i++) {
		wdata = DENALI_PHY_DATA(i);
		mmio_write_32((ddr_cfg_base_addr + DENALI_PHY_REG(i)), wdata);
	}

	/* burst length  DENALI_CTL_35[10:8] */
	rdata = mmio_read_32((ddr_cfg_base_addr + DENALI_CTL_REG(35)));
	wdata = (rdata & ~(DRAM_BSTLEN_BIT_MASK << DRAM_BSTLEN_BIT_OFFSET)) |
					(DRAM_BSTLEN << DRAM_BSTLEN_BIT_OFFSET);
	mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(35)), (wdata));

#ifdef ENABLE_IN_ORDER
	/* set in_order_accept = 1 */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(250));
	wdata = rdata | (0x1 << 8);
	mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(250)), wdata);
#endif

	/* disable rw_group_w_bnk_conflict = 0 */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(247));
	wdata = rdata & ~(0x3 << 8);
	mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(247)), (wdata));

	/* disable cs_same_en */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(246));
	wdata = rdata & ~(0x1 << 24);
	mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(246)), (wdata));

	/* reduce time for IO pad calibration */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_PHY_REG(2365));
	wdata = rdata & ~(0x7f << 24);
	mmio_write_32((ddr_cfg_base_addr + DENALI_PHY_REG(2365)), (wdata));

	/* disable ecc */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(195));
	wdata = rdata & ~(0x3 << 16);
	mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(195)), (wdata));

	/* write start bit to initiate */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(0));
	wdata = rdata | 0x1;
	mmio_write_32((ddr_cfg_base_addr + DENALI_CTL_REG(0)), (wdata));

	/* wait mc initialization has been completed */
	rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(264));
	while (((rdata >> 9) & 0x1) != 1)
		rdata = mmio_read_32(ddr_cfg_base_addr + DENALI_CTL_REG(264));

	udelay(10);
	return 0;
}

void mango_ddr_init_pld(void)
{
	int i;

	for (i = 0; i < MANGO_DDRC_MAX; ++i) {
		NOTICE("Init DDR%d\n", i);
		ddr_init_pld(MANGO_DDRC_BASE + MANGO_DDRC_SIZE * i);
	}
}
