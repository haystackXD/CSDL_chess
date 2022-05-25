#include "texture.h"

bool texture_loadTextureFromFile(struct texture* self, struct gameworld_info* game, const char* path)
{
	SDL_Surface *image;

	image = IMG_Load(path);
	if (!image) 
		debug_log("IMG_Load: %s\n", IMG_GetError());

	self->m_Texture = SDL_CreateTextureFromSurface(game->gRenderer, image);

	if (self->m_Texture == NULL)
		debug_log("Unable to create texture from loaded surface SDL_Error: %s\n", 
				SDL_GetError());

	// Free unused surface
	SDL_FreeSurface(image);
	return false;
}

void texture_free(struct texture *self)
{
	// if texture is not all ready free we will free it
	// by destroying it
	if (self->m_Texture != NULL)
	{
		// destroy texture 
		SDL_DestroyTexture(self->m_Texture);
		self->m_Texture = NULL;

		memset(&self->m_Rect, 0, sizeof(SDL_Rect));
	}
}

void texture_render(
		struct texture *self, 
		struct gameworld_info* game,
		SDL_Rect* coRect,
		double angle,
		SDL_Point* center,
		SDL_RendererFlip flip
		)
{
	SDL_RenderCopyEx(
			game->gRenderer, self->m_Texture, 
			coRect,  &self->m_Rect,
			angle, center, flip
			);
}
