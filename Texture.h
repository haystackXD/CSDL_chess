#ifndef __TEXTURE_H_
#define __TEXTURE_H_ 1

#include "include/utils.h"
#include "GameWorld.h"

struct texture {
	// actual hardware texture
	SDL_Texture* m_Texture;

	// source rectangle for texture
	SDL_Rect m_Rect;
};


// create texture specified file name
void texture_loadTextureFromFile(struct texture *, struct gameworld_info* game, const char *);

// Return texture rectangle 
const SDL_Rect* texture_getTextureRect(struct texture *);

// render texture on renderer device
void texture_render(
		struct texture *, 
		struct gameworld_info*,
		SDL_Rect *, 
		double, 
		SDL_Point *,
		SDL_RendererFlip
		);


void texture_free(struct texture *);

#endif
