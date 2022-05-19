#include "header.h"

// safely return memory
void* safe_alloc(size_t size)
{
	// allocation failure check
	void *addr = malloc(size);
	assert(addr != NULL);

	return addr;
}


// loggng function to exit on failure
void debug_log(char* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	exit(EXIT_FAILURE);
}
