
/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
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
#include <drivers/bitmain/i2c.h>

#include "bm_common.h"

void pcie_cci_disable(void)
{
	// disable cci
	mmio_clrbits_32(0x5fb80000 + 0, 1 << 16);
}

void pcie_set_eq(void)
{
	// fix compatibility issue
	mmio_setbits_32(0x5f800714, 1 << 8);
}

void pcie_ep_enable(void)
{
	// enable pcie ep, set ltssm_en
	mmio_setbits_32(0x5fa00000 + 0x58, 1 << 0);
}

void pcie_set_chip_mode(int mode)
{
	int value = 0x0;

	value = mmio_read_32(0x5fb80000);
	value &= ~(0x3 << 24);
	value |= (mode << 24);
	mmio_write_32(0x5fb80000, value);
}

void pcie_modify_function_bar_size(int function_num, int is_huge_bar)
{
	mmio_write_32((0x5f900000 + 0x10) | (function_num << 16), 0x3ffff1); //set bar0 4M,32bit
	mmio_write_32((0x5f900000 + 0x14) | (function_num << 16), 0x3ffff1); //set bar1 4M,32bit
	if (is_huge_bar == 0x1) {
		mmio_write_32((0x5f900000 + 0x18) | (function_num << 16), 0xfffffff5); //set bar2 huge bar ,64bit
		mmio_write_32((0x5f900000 + 0x1c) | (function_num << 16), 0xf);
	} else
		mmio_write_32((0x5f900000 + 0x18) | (function_num << 16), 0xffff5); //set bar2 1M,64bit
	mmio_write_32((0x5f900000 + 0x20) | (function_num << 16), 0xffff5); //set bar4 1M,64bit
}

void pcie_modify_bar_size(int mode)
{
	switch (mode) {
	case PCIE_FOUR_CHIP_FIRST:
		pcie_modify_function_bar_size(0x3, 0);
	case PCIE_THREE_CHIP_FIRST:
		pcie_modify_function_bar_size(0x2, 0);
	case PCIE_TWO_CHIP_FIRST:
		pcie_modify_function_bar_size(0x1, 0);
		pcie_modify_function_bar_size(0x0, 0);
		break;
	case PCIE_FOUR_CHIP_SECOND:
		pcie_modify_function_bar_size(0x2, 1);
	case PCIE_FOUR_CHIP_THIRD:
		pcie_modify_function_bar_size(0x1, 1);
	case PCIE_FOUR_CHIP_LAST:
		pcie_modify_function_bar_size(0x0, 1);
		break;
	case PCIE_SINGLE_CHIP_MODE:
		pcie_modify_function_bar_size(0x0, 0);
		break;
	default:
		break;
	}
}

void pcie_modify_function_num(int mode)
{
	int value = 0;
	int i = 0;
	int function_num = (mode & 0x3) + 0x1;

	value = mmio_read_32((0x5f800000 + 0xc) | 0 << 16);             // BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_REG
	if (function_num == 0x1)
		mmio_write_32((0x5f800000 + 0xc) | 0 << 16, value & (~(1 << 23))); // set as  single function mode
	else
		mmio_write_32((0x5f800000 + 0xc) | 0 << 16, value | (1 << 23));    // set as  multi-function  mode

	for (i = 0; i < function_num; i++) {
		value = mmio_read_32((0x5f800000 + 0x8) | (i << 16));//function's class_code reg
		mmio_write_32((0x5f800000 + 0x8) | (i << 16), value | (0x1200 << 16)); //set class_code 0x1200
		if (bm_get_chip_id() == CHIP_BM1684X)
			mmio_write_32((0x5f800000) | (i << 16), 0x16861f1c);
		else
			mmio_write_32((0x5f800000) | (i << 16), 0x16841e30);
	}

	for (i = function_num; i < 4; i++) {
		value = mmio_read_32((0x5f800000 + 0x0) | (i << 16));//function's dev_id_vendor_id reg
		mmio_write_32((0x5f800000 + 0x0) | (i << 16), value | 0xffff); //set valid dev_id 0xffff
	}

	if (function_num > 1) {
		value = mmio_read_32(0x5f800718);
		value &= ~0xff;
		value |= function_num - 0x1;
		mmio_write_32(0x5f800718, value); // set max function num
	}
}

void pcie_function_config(int mode)
{
	 /*config function num and modify bar size*/
	mmio_write_32(0x5f8008bc, mmio_read_32(0x5f8008bc) | 0x1); // enable DBI_RO_WR_EN
	pcie_modify_function_num(mode);
	pcie_modify_bar_size(mode);
	mmio_write_32(0x5f8008bc, mmio_read_32(0x5f8008bc) & (~0x1)); // disable DBI_RO_WR_EN
}

int pcie_polling_core_reset(void)
{
	int loop = 0;
	int ret = 0;
	// Wait for pcie0_core_rstn and pcie0_dbi_aresetn
	loop = mmio_read_32(0x500100b0);
	while (!((mmio_read_32(0x5fb80000 + 0x48) & (1 << 5)) && (mmio_read_32(0x5fb80000 + 0x48) & (1 << 6)))) {
		if (loop-- > 0)
			mdelay(1);
		else {
			ret = -1;
			break;
		}
	}
	return ret;
}

void pcie_polling_perst(void)
{
	// Wait for perst by other
	while (!((mmio_read_32(0x5fb80000 + 0x4c) & (1 << 22))))
		;
	while (!((mmio_read_32(0x5fb80000 + 0x4c) & (1 << 22))))
		;
	while (!((mmio_read_32(0x5fb80000 + 0x4c) & (1 << 22))))
		;
}

void pcie_set_ep_link_speed_gen3(int mode)
{
	int value = 0;
	int i = 0;
	int function_num = (mode & 0x3) + 0x1;

	mmio_write_32(0x5f8008bc, mmio_read_32(0x5f8008bc) | 0x1); // enable DBI_RO_WR_EN

	mmio_write_32(0x5f80080c, mmio_read_32(0x5f80080c) | (0x1 << 17)); // enable pcie link change speed

	for (i = 0; i < function_num; i++) {
		value = mmio_read_32((0x5f800000 + 0xa0) | (i << 16));
		value &= ~0xf;
		value |= 0x3;
		mmio_write_32((0x5f800000 + 0xa0) | (i << 16), value); // cap_target_link_speed Gen3

		value = mmio_read_32((0x5f800000 + 0x7c) | (i << 16));
		value &= ~0xf;
		value |= 0x3;
		if (mode != PCIE_SINGLE_CHIP_MODE) {
			value &=  ~(0x3f << 4);
			value |= (0x8 << 4);
		}

		mmio_write_32((0x5f800000 + 0x7c) | (i << 16), value); // cap_max_link_speed Gen3
	}

	mmio_write_32(0x5f8008bc, mmio_read_32(0x5f8008bc) & (~0x1)); // disable DBI_RO_WR_EN
}

void pcie_ep_iatu_config(void)
{
    /*use iATU0 to map pcie controller regs to BAR0 using bar match mode */
	mmio_write_32(0x5fb00114, 0x5F800000);
	mmio_write_32(0x5fb00118, 0x0);
	mmio_write_32(0x5fb00100, 0x0);
	mmio_write_32(0x5fb00104, 0xC0080000); //bar match
}

void pcie_set_ss_mode(int ss_mode)
{
	if (ss_mode == 0x0)
		mmio_write_32(0x5fb80000, mmio_read_32(0x5fb80000) & (~0x1)); //ss_mode[0] = 0; ep only mode
	else
		mmio_write_32(0x5fb80000, mmio_read_32(0x5fb80000) | 0x1);    //ss_mode[0] = 1;  ep and rc mode
}

void pcie_set_repeat_clk(void)
{
	int mode = 0;

	mode = bm_gpio_read(BIT_MASK_GPIO_PCIE_REFCLK);

	if (mode == 0x1) {
		mmio_setbits_32(0x5fa00000 + 0x1000, 1 << 4);
		mmio_clrbits_32(0x5fa00000 + 0x1400, 1 << 5);
		mmio_setbits_32(0x5fa00000 + 0xe4c, 1 << 2);
		udelay(16);
		mmio_clrbits_32(0x5fa00000 + 0xe4c, 1 << 2);
	}
}

void pcie_set_lane_reversal(void)
{
	int mode = 0;
	uint32_t value = 0;

	mode = bm_gpio_read(BIT_MASK_GPIO_PCIE_LANE_REV);

	if (mode == 0x1) {
		value = mmio_read_32(0x5f80080c);
		value &= ~(0x1f << 8);
		value |= (0x4 << 8);
		mmio_write_32(0x5f80080c, value); // lane0-3 reversal
	}
}

void pcie_add_phy_patch(void)
{
	mmio_write_32(0x5fa01034, 0x01c201c2);
	mmio_write_32(0x5fa01434, 0x01c201c2);
	mmio_write_32(0x5fa01030, 0x150400c0);
	mmio_write_32(0x5fa01430, 0x150400c0);
	mmio_write_32(0x5fa01014, 0x00540054);
	mmio_write_32(0x5fa01414, 0x00540054);
	mmio_setbits_32(0x5fa01000, 1 << 13);
	mmio_write_32(0x5fa00e4c, 0x00000606);

	udelay(100);
	mmio_write_32(0x5fa00e4c, 0x00000202);
	udelay(25);
	mmio_write_32(0x5fa00e4c, 0x0);
}

void pcie_set_time_out_value(void)
{
	mmio_write_32(0x500100b0, 0x78);
}

void single_chip_card_init(int mode)
{

	pcie_polling_perst();

	if (pcie_polling_core_reset() < 0)
		return;

	pcie_cci_disable();

	pcie_set_lane_reversal();

	if (mode == PCIE_SINGLE_CHIP_MODE)
		pcie_set_ss_mode(0);
	else if (mode == PCIE_RC_ONLY_MODE)
		pcie_set_ss_mode(1);

	pcie_set_chip_mode(0x1);
	pcie_function_config(PCIE_SINGLE_CHIP_MODE);
	pcie_set_ep_link_speed_gen3(PCIE_SINGLE_CHIP_MODE);
	pcie_ep_iatu_config();

	pcie_set_eq();

	pcie_ep_enable();
}

void muti_chip_card_init(int mode)
{

	pcie_polling_perst();

	if (pcie_polling_core_reset() < 0)
		return;

	pcie_cci_disable();

	pcie_set_ss_mode(0x1);
	pcie_set_chip_mode(0x0);

	pcie_function_config(mode);
	pcie_set_ep_link_speed_gen3(mode);
	pcie_ep_iatu_config();

	pcie_set_eq();

	pcie_ep_enable();
}

#ifdef HAS_PCIE
void bm_pcie_status_init(void)
{
	if ((mmio_read_32(0x5fb80000 + 0x48) & (1 << 5)) &&
	    (mmio_read_32(0x5fb80000 + 0x48) & (1 << 6)) &&
	    (mmio_read_32(0x5fa00000 + 0xb4) & (1 << 6)) &&
	    (mmio_read_32(0x5fa00000 + 0xb4) & (1 << 7))) {

		mmio_setbits_32(BOOT_ARGS_REG, PCIE_EP_LINKED);
	} else {
		unsigned char pcie_check;
		int err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
				  PCIE_CHECK_REG, &pcie_check);

		// pcie_check: 1: SoC mode; 2: PCIe mode; 3: SoC mode but with PCIe EP link
		if (!err) {
			// SC5H pcie_check is always 0xff
			if (pcie_check == 0x2 || pcie_check == 0x3 || pcie_check == 0xff)
				mmio_setbits_32(BOOT_ARGS_REG, PCIE_EP_LINKED);
			if (pcie_check == 0x3)
				mmio_setbits_32(BOOT_ARGS_REG, SOC_EP);
		} else {
			// i2c read failed, force to PCIe mode, for SC7 compatibility
			NOTICE("force to PCIe mode\n");
			mmio_setbits_32(BOOT_ARGS_REG, PCIE_EP_LINKED);
		}
	}
#if defined(CONFIG_ARCH_BM1686_PLD) && defined(HAS_PCIE)
	mmio_setbits_32(BOOT_ARGS_REG, PCIE_MODE);
#endif
}

void bm_pcie_init(void)
{
	int mode = 0x0;

	if (mmio_read_32(BOOT_ARGS_REG) & SKIP_PCIEI)
		return;

	pcie_set_repeat_clk();

	pcie_set_time_out_value();

	pcie_add_phy_patch();

	mode = bm_gpio_read(BIT_MASK_GPIO_PCIE_SEL);

	if (mode == PCIE_SINGLE_CHIP_MODE || mode == PCIE_RC_ONLY_MODE)
		single_chip_card_init(mode);
	else
		muti_chip_card_init(mode);

	bm_dump_nv_counter("PCIe");
}
#else
void bm_pcie_status_init(void)
{
}

void bm_pcie_init(void)
{
}
#endif

