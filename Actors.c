#include "include/utils.h"
#include "Actors.h"

void initChessBoxTexture(struct ActorCollector *self, 
		struct gameworld_info* game,
		int width, 
		int height)
{
	struct texture *textureObj = &self->chessBoxTextureObj;
	SDL_Surface* chessBoxSurface;
	uint8_t idx, idy, box_color = 0x0;

	// Copy single square box in chess Board
	// creating exact copy of first square box
	SDL_Rect tmpRect = {
		0, 0, width, height
	};

	// total size of chessBoard
	textureObj->m_Rect.x = 0;
	textureObj->m_Rect.y = 0;
	textureObj->m_Rect.w = width * 8;
	textureObj->m_Rect.h = height * 8;

	// Create a software level surface to draw chessboard
	// then copy it to hardware texture
	chessBoxSurface = SDL_CreateRGBSurface(0, 
			textureObj->m_Rect.w, 
			textureObj->m_Rect.h,
			32, 						// depth  of color
			0, 0, 0, 0);
	if (chessBoxSurface == NULL)
		debug_log("Unable to create surface for chess Box SDL_Error: %s\n", SDL_GetError());


	for (idy = 0; idy < 8; idy++)
	{
		tmpRect.y = idy * tmpRect.h;
		for (idx = 0; idx < 8; idx++)
		{
			tmpRect.x = idx * tmpRect.w;

			// Set Color code to chess
			SDL_FillRect(chessBoxSurface, &tmpRect, SDL_MapRGB(
						chessBoxSurface->format, 
						box_color,
						box_color, 
						box_color
						));
			// Change colors as we are moving to adjacent box
			box_color = ~box_color;
		}
		tmpRect.x = 0;
		box_color = ~box_color;
	}

	textureObj->m_Texture = SDL_CreateTextureFromSurface(game->gRenderer, chessBoxSurface);
	if (textureObj->m_Texture == NULL)
		debug_log("Unable to create texture from surface SDL_Error: %s\n", 
				SDL_GetError());

	// Free Surface after use
	SDL_FreeSurface(chessBoxSurface);
}


// allocate memory and initilize coordinates
void *createActors(struct gameworld_info* game) 
{
	struct ActorCollector* gameActors;

	// Allocate memory for game actors
	gameActors = safe_alloc(sizeof(struct ActorCollector));

	// initialize chess Board Texture
	initChessBoxTexture(gameActors, game, 100, 100);

	return (void *)gameActors;
}

void renderActors(struct ActorCollector *self, struct gameworld_info* game)
{
	int square_window_dim = min(getWidth(game), getHeight(game));

	SDL_Rect windowRect = {
		.x = (getWidth(game) - square_window_dim) / 2, 
		.y = 0, 
		.w = square_window_dim,
		.h = square_window_dim
	};


	SDL_RenderCopy(
			game->gRenderer, 
			self->chessBoxTextureObj.m_Texture, 
			&self->chessBoxTextureObj.m_Rect, 
			&windowRect
			); 
}
