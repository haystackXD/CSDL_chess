#ifndef __ACTORS_H_
#define __ACTORS_H_ 1

#include "include/utils.h"
#include "gameworld.h"

struct ActorCollector {
	uint8_t box_color;

	struct SDL_Rect mRect;
	struct SDL_Rect chessSquare;
};

void *createActors(void);

void renderActors(struct ActorCollector*, struct gameworld_info *);

#endif
