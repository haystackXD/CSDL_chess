#ifndef GAME_GLOBAL
#define GAME_GLOBAL 1

#define MIN(first, second) (first < second ? first : second)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "SDL.h"
#include "SDL_image.h"

#define errExit(...) do {					\
	fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE);	\
} while (0);

#define array_size(array) (sizeof(array)/sizeof(*array)) 

#endif
