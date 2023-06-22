#include "texture.h"

void loadTextureFromPath(struct texture* self, SDL_Renderer* gRenderer, char* path)
{
	SDL_Surface* finalSurface;

	finalSurface = SDL_LoadBMP(path);
	if (finalSurface == NULL)
		errExit("Cannot find image at path: %s\n", path);

	self->m_Texture = SDL_CreateTextureFromSurface(gRenderer, finalSurface);
	if (self->m_Texture == NULL)
		errExit("Unable to create texture from surface SDL_Error: %s\n", SDL_GetError());

	self->m_Width = finalSurface->w;
	self->m_Height = finalSurface->h;

	// free surface 
	SDL_FreeSurface(finalSurface);
}

