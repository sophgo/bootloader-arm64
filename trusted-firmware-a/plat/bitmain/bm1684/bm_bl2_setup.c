/*
 * Copyright (c) 2015-2019, ARM Limited and Contributors. All rights reserved.
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
#include <dw_gpio.h>

#include "bm_common.h"

/* Data structure which holds the extents of the trusted SRAM for BL2 */
static meminfo_t bl2_tzram_layout __aligned(CACHE_WRITEBACK_GRANULE);

void bl2_early_platform_setup2(u_register_t arg0, u_register_t arg1,
			       u_register_t arg2, u_register_t arg3)
{
	meminfo_t *mem_layout = (void *)arg1;

	bm_reg_base_init();

	/* Initialize the console to provide early debug support */
	bm_console_init();

	/* Setup the BL2 memory layout */
	bl2_tzram_layout = *mem_layout;

	if (bm_get_chip_id() == CHIP_BM1684) {
		/* override boot ROM setting */
		bl2_tzram_layout.total_base = BL2_BASE;
		bl2_tzram_layout.total_size = BL2_LIMIT - BL2_BASE;
	}
}

static void security_setup(void)
{
	/*
	 * This is where a TrustZone address space controller and other
	 * security related peripherals, would be configured.
	 */
}

static int bm_get_board_info(void)
{
	int type = 0;
	unsigned char mcu_type = 0, hw_ver = 0;

#if defined(CONFIG_ARCH_BM1686_PLD)
	type = BM1684X_PLD;
#elif defined(CONFIG_ARCH_BM1686_FPGA)
	type = BM1684X_FPGA;
#else
	int err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
				  HW_TYPE_REG, &mcu_type);
	if (err) {
		ERROR("read board type failed with error %d\n", err);
		mcu_type = MCU_BM1684X_SC7_HP300;
	} else {
		err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
					  HW_VERSION_REG, &hw_ver);
		if (err) {
			ERROR("read hardware version failed with error %d\n", err);
			assert(0);
		}
	}

	if (bm_get_chip_id() == CHIP_BM1684) {
		switch (mcu_type) {
		case MCU_BM1684_EVB:
		case MCU_BM1684_SC5:
			type = BM1684_EVB_V1_2;
			break;
		case MCU_BM1684_SM5_TB:
			if (hw_ver == 0x11)
				type = BM1684_CUST_V1_1;
			else if (hw_ver == 0x12)
				type = BM1684_SM5_V1_2_TB;
			else if (hw_ver == 0x13)
				type = BM1684_CUST_V1_3;
			else if (hw_ver >= 0x14)
				type = BM1684_CUST_V1_4;
			else
				type = BM1684_SM5_V1_2_TB;
			break;
		case MCU_BM1684_SM5_PB:
		case MCU_BM1684_SM5_RB:
			if (hw_ver == 0x11)
				type = BM1684_SM5_V1_1_RB;
			else if (hw_ver == 0x12)
				type = BM1684_SM5_V1_2_RB;
			else
				type = BM1684_SM5_V1_1_RB;
			break;
		case MCU_BM1684_SE5_V1:
			if (hw_ver == 0x13)
				type = BM1684_SE5_V1_3;
			else if (hw_ver == 0x14)
				type = BM1684_SE5_V1_4;
			else
				type = BM1684_SE5_V1_1;
			break;
		case MCU_BM1684_SE5_V2:
			if (hw_ver == 0x20)
				type = BM1684_SE5_V2_0;
			else if (hw_ver == 0x21)
				type = BM1684_SE5_V2_1;
			else if (hw_ver == 0x25)
				type = BM1684_SE5_V2_5;
			else
				type = BM1684_SE5_V2_5;
			break;
		case MCU_BM1684_SC5T:
		case MCU_BM1684_SC5H:
		case MCU_BM1684_SC5P:
			type = BM1684_SC5_EP;
			break;
		case MCU_BM1684_SM5M_PB:
		case MCU_BM1684_SM5M_RB:
			if (hw_ver == 0x00)
				type = BM1684_SM5M_V0_0_RB;
			else if (hw_ver == 0x01)
				type = BM1684_SM5M_V0_1_RB;
			else if (hw_ver == 0x02)
				type = BM1684_SM5M_V0_2_RB;
			else if (hw_ver == 0x30)
				type = BM1684_SM5M_V3_0_RB;
			else if (hw_ver >= 0x31)
				type = BM1684_SM5M_V3_1_RB;
			else
				type = BM1684_SM5M_V0_0_RB;
			break;
		case MCU_BM1684_SM5M_TB:
			if (hw_ver == 0x00)
				type = BM1684_SM5M_V0_0_TB;
			else if (hw_ver == 0x01)
				type = BM1684_SM5M_V0_1_TB;
			else if (hw_ver == 0x02)
				type = BM1684_SM5M_V0_2_TB;
			else if (hw_ver == 0x30)
				type = BM1684_SM5M_V3_0_TB;
			else if (hw_ver >= 0x31)
				type = BM1684_SM5M_V3_1_TB;
			else
				type = BM1684_SM5M_V0_0_TB;
			break;
		case MCU_BM1684_SE6_CTRL:
			type = BM1684_SE6_CTRL;
			break;
		default:
			ERROR("unknown board type %u\n", mcu_type);
			assert(0);
		}

		if ((mmio_read_32(BOOT_ARGS_REG) & PCIE_EP_LINKED) &&
		    !(mmio_read_32(BOOT_ARGS_REG) & SOC_EP))
			type = BM1684_SC5_EP;
	} else {
		switch (mcu_type) {
		case MCU_BM1684X_EVB:
			if (hw_ver == 0x00)
				type = BM1684X_EVB_V0_0;
			break;
		case MCU_BM1684X_SM7M_RB:
			if (hw_ver == 0x00)
				type = BM1684X_SM7M_V0_0_RB;
			break;
		case MCU_BM1684X_SM7M_RB_CTRL:
			if (hw_ver == 0x00)
				type = BM1684X_SM7M_V0_0_RB_CTRL;
			break;
		case MCU_BM1684X_SM7_CTRL:
			if (hw_ver == 0x00)
				type = BM1684X_SM7_CTRL;
			break;
		case MCU_BM1684X_SM7M_CUST_V1:
			if (hw_ver == 0x00)
				type = BM1684X_SM7M_V0_0_CUST_V1;
			break;
		case MCU_BM1684X_SC7_HP300:
			type = BM1684X_EP;
			break;
		case MCU_BM1684X_SE7_V1:
			if (hw_ver == 0x00)
				type = BM1684X_SE7_V1;
			break;
		default:
			ERROR("unknown board type %u\n", mcu_type);
			assert(0);
		}

		if ((mmio_read_32(BOOT_ARGS_REG) & PCIE_EP_LINKED) &&
		    !(mmio_read_32(BOOT_ARGS_REG) & SOC_EP))
			type = BM1684X_EP;
	}
#endif

	NOTICE("%s board type: %d/%d/0x%x\n",
	       bm_get_chip_id() == CHIP_BM1684 ? "BM1684" : "BM1684X",
	       type, mcu_type, hw_ver);
	mmio_write_32(BOARD_TYPE_REG, type);
	return type;
}

static void bm_ddr_init(void)
{
	int default_mode = 0;

	/*
	 * for bm1684:
	 *    mode 0: DDR0A/B interleave, DDR1/2 no interleave
	 *    mode 1: DDR0A/B interleave, DDR1/2 interleave
	 *    mode 2: disable
	 * for bm1684x:
	 *    mode 0: DDR0A/B interleave, DDR1/2 no interleave
	 *    mode 1: DDR0A/DDR0B/DDR1/DDR2 interleave
	 *    mode 2: disable
	 */

	if (bm_get_chip_id() == CHIP_BM1684) {
		default_mode = 0;
	} else {
#ifdef CONFIG_ARCH_BM1686_FPGA
		default_mode = 2;
#else
#ifdef CONFIG_INTLV_MODE0
		default_mode = 0;
#else
		default_mode = 1;
#endif
#endif
	}

	switch (default_mode) {
	case 0:
		mmio_setbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_DDR_INTLV_EN);
		mmio_clrbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_DDR_INTLV_MODE);
		NOTICE("interleave mode 0\n");
		break;
	case 1:
		mmio_setbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_DDR_INTLV_EN);
		mmio_setbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_DDR_INTLV_MODE);
		NOTICE("interleave mode 1\n");
		break;
	case 2:
		mmio_clrbits_32(TOP_BASE + REG_TOP_CTRL, BIT_MASK_TOP_CTRL_DDR_INTLV_EN);
		NOTICE("interleave disabled\n");
	}

#ifdef CONFIG_ARCH_BM1686_PLD
	bm_ddr_init_pld();
#elif defined(CONFIG_ARCH_BM1686_FPGA)
	// workaround for the difference between ASIC and FPGA DDR fabric
	// disable DDR AW W alignment
	mmio_setbits_32(0x500101C0, 0x1);
#else
	bm_ddr_init_asic();
#endif
}

static struct i2c_info i2c_info[] = {
	{ I2C0_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C1_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C2_BASE, 100 * 1000 * 1000, 100 * 1000 },
};

#ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE	64
#endif

static void __unused a53lite_up(void)
{
#ifndef CONFIG_ARCH_BM1686_FPGA
	/* reset a53 lite reset */
	uint32_t *a53lite_park = (void *)A53L_PARK_START;
	uint32_t a53lite_reset_base =
		((unsigned long)a53lite_park >> A53L_PARK_SHIFT) & 0xffffffff;

	a53lite_park[0] = A53L_PARK_INST;

	NOTICE("Setup A53 Lite Reset Address %016lx\n",
	       (unsigned long)a53lite_park);
	mmio_write_32(TOP_BASE + REG_TOP_A53L_RST_VEC, a53lite_reset_base);
	NOTICE("Release A53 Lite\n");
	/* de-assert a53 lite */
	mmio_setbits_32(TOP_BASE + REG_TOP_SOFT_RST0,
			BIT_MASK_TOP_SOFT_RST0_A53L);
#endif
}

void bl2_platform_setup(void)
{
	security_setup();
	generic_delay_timer_init();
	bm_ip_reset();
	bm_pin_init();

	i2c_init(i2c_info, ARRAY_SIZE(i2c_info));
	bm_pcie_status_init();
	bm_get_board_info();

	if ((mmio_read_32(BOOT_ARGS_REG) & PCIE_EP_LINKED) &&
	    !(mmio_read_32(BOOT_ARGS_REG) & SOC_EP))
		NOTICE("skip DDR init\n");
	else
		bm_ddr_init();

	/* release a53 lite reset for debug purpose */
	if (bm_get_chip_id() == CHIP_BM1684X)
		a53lite_up();

	/* pcie mode should record version info before wait fip*/
	bm_storage_boot_loader_version(BL2_VERSION_BASE);
	bm_locate_next_image();
}

void bl2_plat_arch_setup(void)
{
	bm_configure_mmu_el1(bl2_tzram_layout.total_base,
			     bl2_tzram_layout.total_size,
			     BL_CODE_BASE, BL_CODE_END,
			     BL_RO_DATA_BASE, BL_RO_DATA_END,
			     BL_COHERENT_RAM_BASE, BL_COHERENT_RAM_END);
}

/*******************************************************************************
 * Gets SPSR for BL33 entry
 ******************************************************************************/
static uint32_t bm_get_spsr_for_bl33_entry(void)
{
	uint32_t spsr;
	unsigned int mode;

	/* Figure out what mode we enter the non-secure world in */
	mode = (el_implemented(2) != EL_IMPL_NONE) ? MODE_EL2 : MODE_EL1;

	/*
	 * TODO: Consider the possibility of specifying the SPSR in
	 * the FIP ToC and allowing the platform to have a say as
	 * well.
	 */
	spsr = SPSR_64(mode, MODE_SP_ELX, DISABLE_ALL_EXCEPTIONS);

	return spsr;
}

static int bm_bl2_handle_post_image_load(unsigned int image_id)
{
	int err = 0;
	bl_mem_params_node_t *bl_mem_params = get_bl_mem_params_node(image_id);

	assert(bl_mem_params);

	switch (image_id) {
	case BL33_IMAGE_ID:
		/* BL33 expects to receive the primary CPU MPID (through r0) */
		bl_mem_params->ep_info.args.arg0 = 0xffff & read_mpidr();
		bl_mem_params->ep_info.spsr = bm_get_spsr_for_bl33_entry();
		break;
	default:
		/* Do nothing in default case */
		break;
	}

	return err;
}

/*******************************************************************************
 * This function can be used by the platforms to update/use image
 * information for given `image_id`.
 ******************************************************************************/
int bl2_plat_handle_post_image_load(unsigned int image_id)
{
	return bm_bl2_handle_post_image_load(image_id);
}

uintptr_t plat_get_ns_image_entrypoint(void)
{
	return NS_IMAGE_OFFSET;
}
