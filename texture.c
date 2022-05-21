#include "texture.h"

bool texture_loadTextureFromFile(struct texture* self, const char* path)
{
	SDL_Surface *image;

	image = IMG_Load(path);
	if (!image) 
		debug_log("IMG_Load: %s\n", IMG_GetError());

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
		struct gameworld_info *game,
		const SDL_Rect *, 
		const double angle, 
		const SDL_Point *,
		const SDL_RendererFlip
		)
{

}
