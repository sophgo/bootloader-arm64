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

	/* Initialize the console to provide early debug support */
	bm_console_init();

	/* Setup the BL2 memory layout */
	bl2_tzram_layout = *mem_layout;
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
#if defined(CONFIG_ARCH_BM1686_PLD)
	NOTICE("Board type: PLD\n");
	mmio_write_32(BOARD_TYPE_REG, BOARD_PLD);
	return BOARD_PLD;
#elif defined(CONFIG_ARCH_BM1686_FPGA)
	NOTICE("Board type: FPGA\n");
	mmio_write_32(BOARD_TYPE_REG, BOARD_FPGA);
	return BOARD_FPGA;
#else
	int type, err;
	unsigned char mcu_type;

	err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
				  HW_TYPE_REG, &mcu_type);
	if (err) {
		ERROR("read board type failed with error %d\n", err);
		assert(0);
	}
	if (mcu_type != MCU_BOARD_TYPE_EVB) {
		ERROR("unknown board type %u\n", mcu_type);
		assert(0);
	}

	// TOX: support more boards here
	type = BOARD_EVB_V1_0;

	NOTICE("Board type: 0x%x/0x%x\n", type, mcu_type);
	mmio_write_32(BOARD_TYPE_REG, type);
	return type;
#endif
}

static void bm_ddr_init(void)
{
#ifdef DDR_INTERLEAVE_MODE1
	// interleave is enabled mode1 by default (ddr0a/ddr0b/ddr1/ddr2 interleave)
	mmio_setbits_32(TOP_BASE + TOP_CTRL_REG, DDR_INTLV_EN | DDR_INTLV_MODE);
	NOTICE("interleave mode 1\n");
#elif defined(DDR_INTERLEAVE_MODE0)
	// interleave is enabled mode0 (ddr0a/ddr0b interleave)
	mmio_setbits_32(TOP_BASE + TOP_CTRL_REG, DDR_INTLV_EN);
	mmio_clrbits_32(TOP_BASE + TOP_CTRL_REG, DDR_INTLV_MODE);
	NOTICE("interleave mode 0\n");
#else
	//disable 4K interleave
	mmio_clrbits_32(TOP_BASE + TOP_CTRL_REG, DDR_INTLV_EN);
	NOTICE("interleave disabled\n");
#endif

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
}

void bl2_platform_setup(void)
{
	security_setup();
	generic_delay_timer_init();
	bm_ip_reset();
	bm_pin_init();

	i2c_init(i2c_info, ARRAY_SIZE(i2c_info));
	bm_get_board_info();

	bm_pcie_status_init();
	if (!bm_check_pcie_link())
		bm_ddr_init();

#ifdef CONFIG_ARCH_BM1686_PLD
	/* release a53 lite reset for debug purpose */
	a53lite_up();
#endif

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
