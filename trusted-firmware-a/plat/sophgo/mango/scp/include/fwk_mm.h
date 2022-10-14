#ifndef __FWK_MM_H__
#define __FWK_MM_H__

#include <stddef.h>

void *fwk_mm_alloc(size_t num, size_t size);
void *fwk_mm_alloc_notrap(size_t num, size_t size);
void *fwk_mm_alloc_aligned(size_t alignment, size_t num, size_t size);
void *fwk_mm_calloc(size_t num, size_t size);
void *fwk_mm_calloc_aligned(size_t alignment, size_t num, size_t size);
void *fwk_mm_realloc(void *ptr, size_t num, size_t size);
void fwk_mm_free(void *ptr);

#endif
