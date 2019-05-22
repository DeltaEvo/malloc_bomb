#include "common.c"
#include <stdlib.h>

void *malloc(size_t size) {
	if (count_or_fail())
		return (NULL);
	else
		return ((malloc_type)dlsym(RTLD_NEXT, "malloc"))(size);
}

void *r_calloc(size_t nitems, size_t size) {
	if (count_or_fail())
		return (NULL);
	else
		return ((calloc_type)dlsym(RTLD_NEXT, "calloc"))(nitems, size);
}

void *r_realloc(void *ptr, size_t size) {
	if (count_or_fail())
		return (NULL);
	else
		return ((realloc_type)dlsym(RTLD_NEXT, "realloc"))(ptr, size);
}