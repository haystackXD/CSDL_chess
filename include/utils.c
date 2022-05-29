#include "utils.h"


// safely return memory
void* safe_alloc(size_t size)
{
	// allocation failure check
	void *addr = malloc(size);
	assert(addr != NULL);

	return addr;
}


void unorder_init(struct unorder_array* self, 
        unsigned size, 
        size_t len)
{
    self->size = size;
    self->len = len;

    self->data = safe_alloc(self->size * self->len);
}

void unorder_delete(struct unorder_array *self, size_t idx) 
{
    memmove(self->data+self->size*idx, self->data+self->size*--self->len, self->size);
}

void unorder_put(struct unorder_array *self, size_t idx, void *data) 
{
    memcpy(self->data+self->size*idx, data, self->size);
}

void *unorder_get(struct unorder_array *self, size_t idx)
{
    return self->data+self->size*idx;
}

void unorder_free(struct unorder_array *self) 
{ 
    // frees allocated memory and set size of arra
    // to zero 
    free(self->data); 
    self->len = 0; 
}
