#ifndef __HEADER_H_
#define __HEADER_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void *safe_alloc(size_t);
void debug_log(char*, ...);

#endif
