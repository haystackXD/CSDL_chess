#ifndef __ACTORS_H_
#define __ACTORS_H_ 1

#include "include/utils.h"
#include "Texture.h"
#include "GameWorld.h"
#include "playerpieces/player_texture.h"
#include "playerpieces/pawn_piece.h"
#include "playerpieces/queen_piece.h"

struct ActorCollector 
{
	// texture data for chessboard
	struct texture chessBoxObj;

	struct playerTextures* pTexture;

    void *boxes[TOTAL_CHESS_SQUARES];

    struct unorder_array uarray;
};

// allocates memory for actors and initialize them 
// for rendering on the screen
void *createActors(struct gameworld_info*);

// Renders each actor on screen
void renderActors(struct ActorCollector*, struct gameworld_info *);

#endif
