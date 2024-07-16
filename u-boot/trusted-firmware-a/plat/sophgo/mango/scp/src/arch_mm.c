/*
 * Renesas SCP/MCP Software
 * Copyright (c) 2020-2021, Renesas Electronics Corporation. All rights
 * reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <fwk_macros.h>
#include <platform_def.h>

#define HEAP_START	BL31_BASE
#define HEAP_END	BL31_LIMIT

/*!
 * \brief Architecture memory manager context.
 */
static struct arch_mm_ctx {
    uintptr_t heap_break;
    uintptr_t heap_end;
} arch_mm_ctx = {
    .heap_break = (uintptr_t)(HEAP_START),
    .heap_end = (uintptr_t)(HEAP_END),
};

void *_sbrk(intptr_t increment)
{
    if (increment == 0) {
        return (void *)arch_mm_ctx.heap_break;
    } else {
        uintptr_t heap_old = FWK_ALIGN_NEXT(arch_mm_ctx.heap_break, 16);
        uintptr_t heap_new = heap_old + increment;

        if (heap_new > arch_mm_ctx.heap_end) {
            return (void *)-1;
        } else {
            arch_mm_ctx.heap_break = heap_new;

            return (void *)heap_old;
        }
    }
}

void *malloc(size_t size)
{
    void *mem = _sbrk(size);

    if (mem == ((void *)-1))
        mem = NULL;

    return mem;
}

void *calloc(size_t nmemb, size_t size)
{
    void *mem = malloc(nmemb * size);

    if (mem)
        memset(mem, 0, nmemb * size);

    return mem;
}

void free(void *p)
{
}
