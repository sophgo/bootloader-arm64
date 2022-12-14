/*
 * Copyright (c) 2013-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <asm_macros.S>
#include <common/bl_common.h>
#include <platform_def.h>

	.globl	bl2_entrypoint



func bl2_entrypoint
	/*---------------------------------------------
	 * Save arguments x0 - x3 from BL1 for future
	 * use.
	 * ---------------------------------------------
	 */
	mov	x20, x0
	mov	x21, x1
	mov	x22, x2
	mov	x23, x3

	/* ---------------------------------------------
	 * Set the exception vector to something sane.
	 * ---------------------------------------------
	 */
	adr	x0, early_exceptions
	msr	vbar_el1, x0
	isb

	/* ---------------------------------------------
	 * Enable the SError interrupt now that the
	 * exception vectors have been setup.
	 * ---------------------------------------------
	 */
	msr	daifclr, #DAIF_ABT_BIT

	/* ---------------------------------------------
	 * Enable the instruction cache, stack pointer
	 * and data access alignment checks and disable
	 * speculative loads.
	 * ---------------------------------------------
	 */
	mov	x1, #(SCTLR_I_BIT | SCTLR_A_BIT | SCTLR_SA_BIT)
	mrs	x0, sctlr_el1
	orr	x0, x0, x1
	bic	x0, x0, #SCTLR_DSSBS_BIT
	msr	sctlr_el1, x0
	isb

#ifdef CONFIG_ARCH_BM1684
	mov_imm	x0, BL2_BASE
	adrp	x1, bl2_entrypoint
	cmp	x0, x1
	b.eq	no_reloc

	/*
	 * some of BL1's RW data exist in dcache, we must
	 * perform a cache flush here for the later memcpy
	 * to get the right data, after switching from
	 * BL1@EL3 to BL2@EL1.
	 */
	mov_imm	x0, BL1_RW_BASE_OLD
	mov_imm	x1, BL1_RW_SIZE
	bl	flush_dcache_range
	/* backup BL1 RW region */
	mov_imm	x0, BL1_RW_SAVE
	mov_imm x1, BL1_RW_BASE_OLD
	mov_imm x2, BL1_RW_SIZE
	bl	memcpy16

	/*
	 * during bl1, we may have valid entry of the BL2 region
	 * in dcache. these lines must be invalidated, otherwise
	 * when BL2 re-enables MMU, we will get the data in dcache.
	 * as A53's invalidate is actrually flush, so we do it
	 * before relocate BL2.
	 * BL2 image end address was stored in x21 (from x1) by boot ROM.
	 * use it to calculate image length.
	 */
	mov_imm	x0, BL2_BASE
	mov_imm x2, BL2_BASE_OLD
	sub	x1, x21, x2
	bl	inv_dcache_range

	/*
	 * copy BL2 from old position (by boot ROM) to new (link address)
	 * calculate BL2 image length from x21 again.
	 */
	mov_imm	x0, BL2_BASE
	mov_imm x1, BL2_BASE_OLD
	sub	x2, x21, x1
	bl	memcpy16_safe
	/* restore x0-x3, although our new BL2 does not use these */
	mov	x0, x20
	mov	x1, x21
	mov	x2, x22
	mov	x3, x23
	/* just invalidate icache, as dcache is not enabled yet */
	ic      ialluis
	isb     sy
	/* jump to new posision of BL2 */
	mov_imm	x4, BL2_BASE
	br	x4
no_reloc:
#endif

	/* ---------------------------------------------
	 * Invalidate the RW memory used by the BL2
	 * image. This includes the data and NOBITS
	 * sections. This is done to safeguard against
	 * possible corruption of this memory by dirty
	 * cache lines in a system cache as a result of
	 * use by an earlier boot loader stage.
	 * ---------------------------------------------
	 */
	adr	x0, __RW_START__
	adr	x1, __RW_END__
	sub	x1, x1, x0
	bl	inv_dcache_range

	/* ---------------------------------------------
	 * Zero out NOBITS sections. There are 2 of them:
	 *   - the .bss section;
	 *   - the coherent memory section.
	 * ---------------------------------------------
	 */
	adrp	x0, __BSS_START__
	add	x0, x0, :lo12:__BSS_START__
	adrp	x1, __BSS_END__
	add	x1, x1, :lo12:__BSS_END__
	sub	x1, x1, x0
	bl	zeromem

#if USE_COHERENT_MEM
	adrp	x0, __COHERENT_RAM_START__
	add	x0, x0, :lo12:__COHERENT_RAM_START__
	adrp	x1, __COHERENT_RAM_END_UNALIGNED__
	add	x1, x1, :lo12:__COHERENT_RAM_END_UNALIGNED__
	sub	x1, x1, x0
	bl	zeromem
#endif

	/* --------------------------------------------
	 * Allocate a stack whose memory will be marked
	 * as Normal-IS-WBWA when the MMU is enabled.
	 * There is no risk of reading stale stack
	 * memory after enabling the MMU as only the
	 * primary cpu is running at the moment.
	 * --------------------------------------------
	 */
	bl	plat_set_my_stack

	/* ---------------------------------------------
	 * Initialize the stack protector canary before
	 * any C code is called.
	 * ---------------------------------------------
	 */
#if STACK_PROTECTOR_ENABLED
	bl	update_stack_protector_canary
#endif

	/* ---------------------------------------------
	 * Perform BL2 setup
	 * ---------------------------------------------
	 */
	mov	x0, x20
	mov	x1, x21
	mov	x2, x22
	mov	x3, x23
	bl	bl2_setup

#if ENABLE_PAUTH
	/* ---------------------------------------------
	 * Program APIAKey_EL1
	 * and enable pointer authentication.
	 * ---------------------------------------------
	 */
	bl	pauth_init_enable_el1
#endif /* ENABLE_PAUTH */

	/* ---------------------------------------------
	 * Jump to main function.
	 * ---------------------------------------------
	 */
	bl	bl2_main

	/* ---------------------------------------------
	 * Should never reach this point.
	 * ---------------------------------------------
	 */
	no_ret	plat_panic_handler

endfunc bl2_entrypoint
