#include "include/utils.h"
#include "Actors.h"

void initStartBox(struct ActorCollector* self)
{
	self->chessSquare.x = 0;
	self->chessSquare.y = 0;
	self->chessSquare.w = 80; 
	self->chessSquare.h = 80;

	self->box_color = 0x0;
}

// allocate memory and initilize coordinates
void *createActors(void) 
{
	struct ActorCollector* gameActors;

	// Allocate memory for game actors
	gameActors = safe_alloc(sizeof(struct ActorCollector));

	gameActors->mRect.x = 0;
	gameActors->mRect.y = 0;
	gameActors->mRect.w = 80;
	gameActors->mRect.h = 80;

	initStartBox(gameActors);

	return (void *)gameActors;
}

void renderActors(struct ActorCollector *self, struct gameworld_info* game)
{
	size_t idx, idy;

	for (idy = 0; idy < 8; idy++)
	{
		self->chessSquare.y = idy * self->chessSquare.h;
		for (idx = 0; idx < 8; idx++)
		{
			self->chessSquare.x = idx * self->chessSquare.w;

			// Set Color code to chess
			SDL_SetRenderDrawColor(game->gRenderer, 
					self->box_color, self->box_color, self->box_color, 0xff);

			// Draw Rectangle on device
			SDL_RenderFillRect(game->gRenderer, &self->chessSquare);

			self->box_color = ~self->box_color;
		}
		self->chessSquare.x = 0;
		self->box_color = ~self->box_color;
	}
	initStartBox(self);
}
