#ifndef __ACTORS_H_
#define __ACTORS_H_ 1

#include "include/utils.h"
#include "texture.h"
#include "gameworld.h"

struct ActorCollector {

	struct SDL_Rect mRect;
	struct texture chessBoxTextureObj;
};

void *createActors(struct gameworld_info*);

void renderActors(struct ActorCollector*, struct gameworld_info *);

#endif
