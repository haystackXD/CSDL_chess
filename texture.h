#ifndef __TEXTURE_H_
#define __TEXTURE_H_ 1

#include "include/utils.h"

struct texture {
	// actual hardware texture
	SDL_Texture* m_Texture;

	// Texture dimesnions
	SDL_Rect m_Rect;

};


// create texture specified file name
bool texture_loadTextureFromFile(struct texture *, const char *);

// Return texture rectangle 
const SDL_Rect* texture_getTextureRect(struct texture *);

// render texture on renderer device
void texture_render(
		struct texture *, 
		SDL_Renderer*,
		const SDL_Rect *, 
		const double, 
		const SDL_Point *,
		const SDL_RendererFlip
		);


void texture_free(struct texture *);

#endif
