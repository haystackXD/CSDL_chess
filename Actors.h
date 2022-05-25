#ifndef __ACTORS_H_
#define __ACTORS_H_ 1

#include "include/utils.h"
#include "texture.h"
#include "gameworld.h"
#include "players/pawn.h"

struct ActorCollector {

	// texture data for chessboard
	struct texture chessBoxTextureObj;

	struct pawn_struct blackPawnPieces;
};

// allocates memory for actors and initialize them 
// for rendering on the screen
void *createActors(struct gameworld_info*);

// Renders each actor on screen
void renderActors(struct ActorCollector*, struct gameworld_info *);

#endif
