#include "common.c"
#include <stdlib.h>

#define DYLD_INTERPOSE(_replacement,_replacee) \
    __attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
    __attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

void *r_malloc(size_t size) {
	if (count_or_fail())
		return (NULL);
	else
		return malloc(size);
}

void *r_calloc(size_t nitems, size_t size) {
	if (count_or_fail())
		return (NULL);
	else
		return calloc(nitems, size);
}

void *r_realloc(void *ptr, size_t size) {
	if (count_or_fail())
		return (NULL);
	else
		return realloc(ptr, size);
}

DYLD_INTERPOSE(r_malloc, malloc);
DYLD_INTERPOSE(r_calloc, calloc);
DYLD_INTERPOSE(r_realloc, realloc);