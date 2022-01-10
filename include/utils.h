#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TOTAL_CHESS_SQUARES 64

#define min(num1, num2) ((num1 > num2) ? num2 : num1)

#define debug_log(...) 	do {	 	\
	fprintf(stderr, __VA_ARGS__);	\
	exit(EXIT_FAILURE);		\
} while (0)


void *safe_alloc(size_t);

