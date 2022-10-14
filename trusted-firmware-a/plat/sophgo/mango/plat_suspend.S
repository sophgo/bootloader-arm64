/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <arch.h>
#include <asm_macros.S>
#include <assert_macros.S>
#include <platform_def.h>

#define PWRCTL_PD (1 << 0)
#define PWRCTL_RFR (1 << 5)

#define TOP_DIS_INTERLEAVE 0x8

	.globl bm_enter_suspend
	//.globl resume_sram_addr

func bm_enter_suspend
	/*
	 * copy execution code to SRAM
	 */
	adr x1, suspend_enter
	ldr x0, =BL2_BASE
	mov x5, x0
	adr x2, suspend_end
copy_s:
	ldp w3, w4, [x1], #0x8
	stp w3, w4, [x0], #0x8
	cmp x1, x2
	bne copy_s
	br x5
suspend_enter:
	/* here set ddr dmc enter self refresh */
#ifdef DDR_ENTER_REFRESH
#endif
	isb
	dsb sy
	wfi
#ifdef DDR_ENTER_REFRESH
#endif
	ret
endfunc bm_enter_suspend

.align 3
suspend_end:
	.word 0xff
