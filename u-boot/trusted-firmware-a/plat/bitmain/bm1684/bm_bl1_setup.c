/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <platform_def.h>
#include <arch.h>
#include <arch_helpers.h>
#include <common/bl_common.h>
#include <lib/mmio.h>
#include <lib/cli.h>
#include <drivers/generic_delay_timer.h>
#include <plat/common/platform.h>
#include <dw_gpio.h>

#include "bm_common.h"

/* Data structure which holds the extents of the trusted SRAM for BL1*/
static meminfo_t bl1_tzram_layout;

meminfo_t *bl1_plat_sec_mem_layout(void)
{
	return &bl1_tzram_layout;
}

/*******************************************************************************
 * Perform any BL1 specific platform actions.
 ******************************************************************************/
void bl1_early_platform_setup(void)
{
	bm_reg_base_init();

	/* Initialize the console to provide early debug support */
	bm_console_init();

	generic_delay_timer_init();
	bm_pin_init();
	bm_pcie_init();

#ifdef BL1_TEST_MODE
	NOTICE("BL1 TEST MODE\n");
	{
		uint64_t val = read_sctlr_el3();

		val |= SCTLR_C_BIT;
		write_sctlr_el3(val);
	}
	cli_loop(0);
#endif

	/* Allow BL1 to see the whole Trusted RAM */
	bl1_tzram_layout.total_base = BL_RAM_BASE;
	bl1_tzram_layout.total_size = BL_RAM_SIZE;

	write_cntfrq_el0(plat_get_syscnt_freq2());
}

/******************************************************************************
 * Perform the very early platform specific architecture setup.  This only
 * does basic initialization. Later architectural setup (bl1_arch_setup())
 * does not do anything platform specific.
 *****************************************************************************/
void bl1_plat_arch_setup(void)
{
	NOTICE("BOOT: %x/%x/%x\n",
	       mmio_read_32(TOP_BASE + REG_TOP_ARM_BOOT_ADDR),
	       bm_gpio_read(BIT_MASK_GPIO_MODE_SEL),
	       bm_gpio_read(BIT_MASK_GPIO_BOOT_SEL));

	bm_configure_mmu_el3(bl1_tzram_layout.total_base,
			     bl1_tzram_layout.total_size,
			     BL_CODE_BASE, BL1_CODE_END,
			     BL1_RO_DATA_BASE, BL1_RO_DATA_END,
			     BL_COHERENT_RAM_BASE, BL_COHERENT_RAM_END);
}

void bl1_platform_setup(void)
{
	cli_loop(-1);
	bm_locate_next_image();

	if (mmio_read_32(BOOT_STAGE_REG) ==  BOOT_START)
		mmio_write_32(BOOT_STAGE_REG, BOOT_WDTED); // not cold boot, previous boot not successful
	else
		mmio_write_32(BOOT_STAGE_REG, BOOT_START);
	bm_wdt_start(15);
	bm_storage_boot_loader_version(BL1_VERSION_BASE);
}
