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
#include <lib/cli.h>
#include <lib/mmio.h>
#include <plat/common/platform.h>
#include <drivers/delay_timer.h>
#include <drivers/generic_delay_timer.h>
#include <drivers/bitmain/i2c.h>
#include <drivers/sophgo/mango_ddr.h>
#include <drivers/sophgo/mango_pcie.h>
#include <dw_gpio.h>

#include "mango_common.h"
#include "mango_misc.h"

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

	/* override boot ROM setting */
	bl2_tzram_layout.total_base = BL2_BASE;
	bl2_tzram_layout.total_size = BL2_LIMIT - BL2_BASE;
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

#if defined(CONFIG_ARCH_MANGO_PLD)
	type = MANGO_PLD;
#elif defined(CONFIG_ARCH_MANGO_FPGA)
	type = MANGO_FPGA;
#else
	int err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
				  HW_TYPE_REG, &mcu_type);
	if (err) {
		ERROR("read board type failed with error %d\n", err);
		assert(0);
	}
	err = i2c_smbus_read_byte(MCU_I2C_DEV, MCU_DEV_ADDR,
				  HW_VERSION_REG, &hw_ver);
	if (err) {
		ERROR("read hardware version failed with error %d\n", err);
		assert(0);
	}

	switch (mcu_type) {
	case MCU_MANGO_EVB:
		if (hw_ver == 0x00)
			type = MANGO_EVB_V0_0;
		break;
	default:
		ERROR("unknown board type %u\n", mcu_type);
		assert(0);
	}
#endif

	NOTICE("%s board type: %d/%d/0x%x\n",
	       "MANGO", type, mcu_type, hw_ver);
	mmio_write_32(BOARD_TYPE_REG, type);

	return type;
}

static struct i2c_info i2c_info[] = {
	{ I2C0_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C1_BASE, 100 * 1000 * 1000, 100 * 1000 },
	{ I2C2_BASE, 100 * 1000 * 1000, 100 * 1000 },
};

#ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE	64
#endif

void bl2_platform_setup(void)
{
	security_setup();
	generic_delay_timer_init();
	bm_ip_reset();
	bm_pin_init();

	i2c_init(i2c_info, ARRAY_SIZE(i2c_info));
	bm_get_board_info();

#ifndef CONFIG_ARCH_MANGO_FPGA
	mango_ddr_init();
#ifdef MANGO_HAS_CMN
	mango_bl2_multi_socket_init();
#endif
#ifdef MANGO_HAS_PCIE
	mango_pcie_init(PCIE_ID_0, PCIE_OP_MODE_RC, PCIE_LINK0_X16, PCIE_LINK_SPEED_16G);
#endif

#endif

	bm_locate_next_image();
#ifdef MANGO_ENABLE_BL2_TEST
	cli_loop(0);
#endif
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
