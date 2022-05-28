#include "utils.h"

// safely return memory
void* safe_alloc(size_t size)
{
	// allocation failure check
	void *addr = malloc(size);
	assert(addr != NULL);

	return addr;
}

