#ifndef __UTILS_H_
#define __UTILS_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>
	
#define SCREEN_WIDTH 	640
#define SCREEN_HEIGHT 	480

#define TOTAL_CHESS_ROWS 8
#define TOTAL_CHESS_COLS 8

#define TOTAL_CHESS_SQUARES (TOTAL_CHESS_ROWS * TOTAL_CHESS_COLS)

#define min(num1, num2) ((num1 > num2) ? num2 : num1)

#define debug_log(...) 	do {	 	\
	fprintf(stderr, __VA_ARGS__);	\
	exit(EXIT_FAILURE);		\
} while (0)

struct unorder_array
{
    unsigned size;
    void *data;
    size_t len;
};


void *safe_alloc(size_t);

// initlize unorder array 
void unorder_init(struct unorder_array* self, unsigned size, size_t len);

// delete element from array swapping array element with last
// element and decreasing length
void unorder_delete(struct unorder_array *self, size_t idx);

// puts data in supplied index
void unorder_put(struct unorder_array *self, size_t idx, void *data);

// gets data from supplied index
void *unorder_get(struct unorder_array *self, size_t idx);

// frees allocated memory
void unorder_free(struct unorder_array *self);


#endif
