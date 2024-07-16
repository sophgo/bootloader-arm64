#include <fwk_mm.h>
#include <fwk_assert.h>

#include <stdlib.h>
#include <string.h>

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *p);

void *fwk_mm_alloc(size_t num, size_t size)
{
    void *ptr = malloc(num * size);

    if (ptr == NULL) {
        fwk_trap();
    }

    return ptr;
}

void *fwk_mm_alloc_notrap(size_t num, size_t size)
{
    return malloc(num * size);
}

void *fwk_mm_calloc(size_t num, size_t size)
{
    void *ptr = calloc(num, size);
    if (ptr == NULL) {
        fwk_trap();
    }

    return ptr;
}

void fwk_mm_free(void *ptr)
{
    free(ptr);
}
