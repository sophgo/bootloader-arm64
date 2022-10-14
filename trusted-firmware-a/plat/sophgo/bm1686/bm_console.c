/*
 * Copyright (c) 2015-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>
#include <drivers/console.h>
#include <drivers/ti/uart/uart_16550.h>

#include "bm_common.h"

static console_t console;

static uint32_t bm_get_uart_clock(void)
{
	uint32_t clk_in_hz;
	uint32_t mode_sel = bm_gpio_read(BIT_MASK_GPIO_MODE_SEL);

	switch (mode_sel) {
	case MODE_NORMAL:
		clk_in_hz = PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL;
		break;
	case MODE_FAST:
		clk_in_hz = PLAT_BM_BOOT_UART_CLK_IN_HZ_FAST;
		break;
	case MODE_SAFE:
		clk_in_hz = PLAT_BM_BOOT_UART_CLK_IN_HZ_SAFE;
		break;
	case MODE_BYPASS:
		clk_in_hz = PLAT_BM_BOOT_UART_CLK_IN_HZ_BYPASS;
		break;
	default:
		clk_in_hz = PLAT_BM_BOOT_UART_CLK_IN_HZ_NORMAL;
		break;
	}
	return clk_in_hz;
}

void bm_console_init(void)
{
	(void)console_16550_register(PLAT_BM_BOOT_UART_BASE,
				     bm_get_uart_clock(),
				     PLAT_BM_CONSOLE_BAUDRATE, &console);

	console_set_scope(&console, CONSOLE_FLAG_BOOT |
			  CONSOLE_FLAG_RUNTIME);
}

