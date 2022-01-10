#include "texture.h"

bool texture_loadTextureFromFile(struct texture* self, const char* path)
{
	SDL_Surface *image;

	image = IMG_Load(path);
	if (!image) 
		debug_log("IMG_Load: %s\n", IMG_GetError());

	return false;
}

void texture_free(struct texture *self)
{
	if (self->m_Texture != NULL)
	{
		// destroy texture 
		SDL_DestroyTexture(self->m_Texture);

		self->m_Rect.x = 0;
		self->m_Rect.y = 0;

		self->m_Rect.w = 0;
		self->m_Rect.h = 0;
	}
}

void texture_render(
		struct texture *self, 
		SDL_Renderer* gRenderer,
		const SDL_Rect * coRect, 
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip
		)
{
	SDL_RenderCopy(gRenderer, self->m_Texture, NULL, NULL);
}

const SDL_Rect* texture_getTextureRect(struct texture *self)
{
	return &self->m_Rect;
}
