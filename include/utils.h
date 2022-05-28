#pragma once

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


void *safe_alloc(size_t);

