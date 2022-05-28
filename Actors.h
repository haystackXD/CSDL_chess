#ifndef __ACTORS_H_
#define __ACTORS_H_ 1

#include "include/utils.h"
#include "Texture.h"
#include "GameWorld.h"
#include "playerpieces/player_texture.h"
//#include "playerpieces/pawn_piece.h"

struct ActorCollector {

	// texture data for chessboard
	struct texture chessBoxTextureObj;

	struct playerTextures* pTextures;

//	struct piece_struct blackPieces[2 * TOTAL_CHESS_COLS];
//	struct piece_struct whitePieces[2 * TOTAL_CHESS_COLS];
};

// allocates memory for actors and initialize them 
// for rendering on the screen
void *createActors(struct gameworld_info*);

// Renders each actor on screen
void renderActors(struct ActorCollector*, struct gameworld_info *);

#endif
