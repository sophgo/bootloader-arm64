/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>
#include <drivers/sophgo/mango_ddr.h>

/* DDR Initialize entry */
void mango_ddr_init(void)
{
#ifdef CONFIG_ARCH_MANGO_PLD
	mango_ddr_init_pld();
#else
	mango_ddr_init_asic();
#endif
}

