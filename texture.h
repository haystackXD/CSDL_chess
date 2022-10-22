#ifndef GAMETEXTURE
#define GAMETEXTURE 1

#include "global.h"

struct texture {
	SDL_Texture* m_Texture;
	int m_Width;
	int m_Height;
};

void loadTextureFromPath(struct texture*, SDL_Renderer*, char*);
#endif
