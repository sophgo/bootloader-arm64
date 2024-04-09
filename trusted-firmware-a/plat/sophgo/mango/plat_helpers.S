/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <assert_macros.S>
#include <platform_def.h>

	.globl	plat_my_core_pos
	.globl	plat_get_my_entrypoint
	.globl	platform_mem_init
	.globl	bm_calc_core_pos
	.globl	plat_crash_console_init
	.globl	plat_crash_console_putc
	.globl	plat_crash_console_flush
	.globl  plat_secondary_cold_boot_setup
	.globl  plat_get_my_entrypoint
	.globl  plat_is_my_cpu_primary
	.globl  plat_non_primary_suspend
	.globl  plat_off_mmu
	.globl  plat_primary_suspend
	.globl	memcpy16_safe
	.globl	invalidate_icache_all

func plat_my_core_pos
	mrs	x0, mpidr_el1
	b	bm_calc_core_pos
endfunc plat_my_core_pos

/*
 *  unsigned int bm_calc_core_pos(u_register_t mpidr);
 *  With this function: CorePos = (ClusterId * 4) + CoreId
 */
func bm_calc_core_pos
	and	x1, x0, #MPIDR_CPU_MASK
	and	x0, x0, #MPIDR_CLUSTER_MASK
	add	x0, x1, x0, LSR #6
	ret
endfunc bm_calc_core_pos

	/* -----------------------------------------------------
	 * unsigned int plat_is_my_cpu_primary (void);
	 *
	 * Find out whether the current cpu is the primary
	 * cpu.
	 * -----------------------------------------------------
	 */
func plat_is_my_cpu_primary
	mrs	x0, mpidr_el1
	and	x0, x0, #(MPIDR_CLUSTER_MASK | MPIDR_CPU_MASK)
	cmp	x0, #MANGO_PRIMARY_CPU
	cset	w0, eq
	ret
endfunc plat_is_my_cpu_primary

	/* -----------------------------------------------------
	 * void plat_secondary_cold_boot_setup (void);
	 *
	 * This function performs any platform specific actions
	 * needed for a secondary cpu after a cold reset e.g
	 * mark the cpu's presence, mechanism to place it in a
	 * holding pen etc.
	 * -----------------------------------------------------
	 */
func plat_secondary_cold_boot_setup
	/* Calculate address of our hold entry */
	bl	plat_my_core_pos
	lsl	x0, x0, #PLAT_MANGO_HOLD_ENTRY_SHIFT
	mov_imm	x2, PLAT_MANGO_HOLD_BASE

	/* clean random value in SRAM first */
	str	xzr, [x2, x0]

	/* Wait until we have a go */
poll_mailbox:
	ldr	x1, [x2, x0]
	cbz	x1, 1f
	mov_imm	x0, PLAT_MANGO_TRUSTED_MAILBOX_BASE
	ldr	x1, [x0]
	br	x1
1:
	wfe
	b	poll_mailbox
endfunc plat_secondary_cold_boot_setup

func plat_get_my_entrypoint
	/* TODO support warm boot */
	mov	x0, #0
	ret
endfunc plat_get_my_entrypoint

func platform_mem_init
	ret
endfunc platform_mem_init

	/* ---------------------------------------------
	 * int plat_crash_console_init(void)
	 * Function to initialize the crash console
	 * without a C Runtime to print crash report.
	 * Clobber list : x0, x1, x2
	 * ---------------------------------------------
	 */
func plat_crash_console_init
	mov_imm x0, PLAT_MANGO_CRASH_UART_BASE
	mov_imm x1, PLAT_MANGO_CRASH_UART_CLK_IN_HZ
	mov_imm x2, PLAT_MANGO_CONSOLE_BAUDRATE
	b	console_16550_core_init
endfunc plat_crash_console_init

	/* ---------------------------------------------
	 * int plat_crash_console_putc(int c)
	 * Function to print a character on the crash
	 * console without a C Runtime.
	 * Clobber list : x1, x2
	 * ---------------------------------------------
	 */
func plat_crash_console_putc
	mov_imm	x1, PLAT_MANGO_CRASH_UART_BASE
	b	console_16550_core_putc
endfunc plat_crash_console_putc

	/* ---------------------------------------------
	 * int plat_crash_console_flush(int c)
	 * Function to force a write of all buffered
	 * data that hasn't been output.
	 * Out : return -1 on error else return 0.
	 * Clobber list : x0, x1
	 * ---------------------------------------------
	 */
func plat_crash_console_flush
	mov_imm	x0, PLAT_MANGO_CRASH_UART_BASE
	b	console_16550_core_flush
endfunc plat_crash_console_flush

func plat_off_mmu
	mrs x1, SCTLR_EL1
	mov x2, #SCTLR_M_BIT
	bic x1, x1, x2 	/* MMU disable. */
	msr SCTLR_EL3, x1
	isb
	ret
endfunc plat_off_mmu

func invalidate_icache_all
	ic	ialluis
	isb	sy
	ret
endfunc invalidate_icache_all

func plat_non_primary_suspend
	bl plat_off_mmu

	ldr x0, =TOP_BASE
	ldr x1, [x0, #REG_TOP_ARM_BOOT_ADDR_L]

	/* Jump to Rom for waiting Mailbox */
	br x1
endfunc plat_non_primary_suspend

func plat_primary_suspend
	bl plat_off_mmu
	bl bm_enter_suspend
	bl bl31_warm_entrypoint
	b el3_exit
endfunc plat_primary_suspend

/* --------------------------------------------------------------------------
 * void memcpy16_safe(void *dest, const void *src, unsigned int length)
 *
 * Copy length bytes from memory area src to memory area dest.
 * The memory areas can be overlapped for at most (length - 16) bytes.
 * Destination and source addresses must be 16-byte aligned.
 *
 * For easy coding, here we may copy more bytes than needed (extend to
 * 16-byte aligned length), so use it with causion!
 * --------------------------------------------------------------------------
 */
func memcpy16_safe
/*
 * x0: original destination
 * x1: original source
 * x2: original length
 * x3: 16-byte aligned length, without tail
 * x4: tail length, not used
 * x5: 16-byte aligned source
 * x6: 16-byte aligned destination
 * x7, x8: the 16byte data
 */
	lsr	x3, x2, #4
	lsl	x3, x3, #4
	sub	x4, x2, x3
	add	x5, x1, x3
	add	x6, x0, x3
/* start from the 16-byte aligned address, so we copy at most 16 bytes more than needed */
ms_loop16:
	ldp	x7, x8, [x5], #0
	stp	x7, x8, [x6], #0
	sub	x5, x5, #16
	sub	x6, x6, #16
	cmp	x5, x1
	b.ge	ms_loop16
	ret
endfunc memcpy16_safe

