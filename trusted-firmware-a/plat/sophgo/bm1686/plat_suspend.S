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

	.macro ddr_srf_pd_enter, dctrl_base
		/* disable 4KB interleave */
		ldr w0, STR_TOP_BASE
		ldr w1, [x0, #0x8]
		bic w1, w1, #TOP_DIS_INTERLEAVE
		str w1, [x0, #0x8]

		/* enter sw refresh */
		mov x0, #\dctrl_base
		ldr w1, [x0, #0x30]
		mov w2, #(/*PWRCTL_PD | */PWRCTL_RFR)
		orr w2, w1, w2
		str w2, [x0, #0x30]
	.endm

	.macro ddr_srf_pd_exit, dctrl_base
		/* enable 4KB interleave */
		ldr w0, STR_TOP_BASE
		ldr w1, [x0, #0x8]
		orr w1, w1, #TOP_DIS_INTERLEAVE
		str w1, [x0, #0x8]

		/* exit sw refresh */
		mov x0, #\dctrl_base
		ldr w1, [x0, #0x30]
		mov w2, #(/*PWRCTL_PD | */PWRCTL_RFR)
		bic w1, w1, w2
		str w1, [x0, #0x30]
	.endm

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
	isb
	dsb sy
	ddr_srf_pd_enter DDR_CTRL0_A
	ddr_srf_pd_enter DDR_CTRL0_B
	ddr_srf_pd_enter DDR_CTRL1
	ddr_srf_pd_enter DDR_CTRL2
#endif
	isb
	dsb sy
	wfi
#ifdef DDR_ENTER_REFRESH
	ddr_srf_pd_exit DDR_CTRL0_A
	ddr_srf_pd_exit DDR_CTRL0_B
	ddr_srf_pd_exit DDR_CTRL1
	ddr_srf_pd_exit DDR_CTRL2
#endif
	ret
endfunc bm_enter_suspend

.align 3
STR_TOP_BASE:
	.word TOP_BASE
suspend_end:
	.word 0xff
