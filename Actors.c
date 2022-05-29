#include "include/utils.h"
#include "Actors.h"
#include "playerpieces/pawn_piece.h"

void initChessBoxTexture(struct ActorCollector *self, 
		struct gameworld_info* game,
		int width, 
		int height)
{
	struct texture *textureObj = &self->chessBoxObj;
	SDL_Surface* chessBoxSurface;
	uint8_t idx, idy, box_color = 0xaf;

	// Copy single square box in chess Board
	// creating exact copy of first square box
	SDL_Rect tmpRect = {
		0, 0, width, height
	};

	// Create a software level surface to draw chessboard
	// then copy it to hardware texture
	chessBoxSurface = SDL_CreateRGBSurface(0, 
			tmpRect.w * 8,
			tmpRect.h * 8,
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
    uint8_t idx, inc = 0;
    struct piece_struct *tmp;

	// Allocate memory for game actors
	gameActors = safe_alloc(sizeof(struct ActorCollector));

	// initialize chess Board Texture
	initChessBoxTexture(gameActors, game, 100, 100);

	gameActors->pTexture = load_players_texture(game);

    // set all pointer to null
    memset(gameActors->boxes, 0, TOTAL_CHESS_SQUARES * sizeof(void *));

    // initialize array of unorder elements with size 16 * sizeof(struct piece_struct)
    unorder_init(&gameActors->uarray, sizeof(struct piece_struct), 16);


    for (idx = 0; idx < 8; idx++)
    {
        tmp = unorder_get(&gameActors->uarray, idx);
        pawn_init(tmp, gameActors->pTexture->blackPawn, 1, idx);
        
        gameActors->boxes[1 * 8 + idx] = tmp;
    }

    for (inc = 0; idx < 16; idx++, inc++)
    {
        tmp = unorder_get(&gameActors->uarray, idx);
        pawn_init(tmp, gameActors->pTexture->whitePawn, 6, inc);

        gameActors->boxes[6 * 8 + inc] = tmp;
    }

	return (void *)gameActors;
}


void renderActors(struct ActorCollector *self, struct gameworld_info* game)
{
	int square_window_dim = min(getWidth(game), getHeight(game));
    struct piece_struct *tmp;

	SDL_Rect *m_Rect = &self->chessBoxObj.m_Rect;

	self->chessBoxObj.m_Rect.x = (getWidth(game) - square_window_dim) / 2; 
	self->chessBoxObj.m_Rect.y = (getHeight(game) - square_window_dim) / 2;
	self->chessBoxObj.m_Rect.w = square_window_dim;
	self->chessBoxObj.m_Rect.h = square_window_dim;

	SDL_RenderCopy(game->gRenderer, 
			self->chessBoxObj.m_Texture,
			NULL, 
			&self->chessBoxObj.m_Rect);


    for (uint8_t idx = 0; idx < self->uarray.len; idx++)
    {
        tmp = unorder_get(&self->uarray, idx);
        tmp->pinterface->render(tmp, game);
    }
}

void freeActors(struct ActorCollector *self)
{
    unorder_free(&self->uarray);
	destroy_playerTextures(self->pTexture);
}
