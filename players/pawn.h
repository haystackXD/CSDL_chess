#ifndef _PAWN_PIECE_
#define _PAWN_PIECE_ 1
#include "../include/utils.h"
#include "../texture.h"

struct pawn_struct {
	struct texture m_Piece[8];
};

void initPawns(struct pawn_struct *, struct gameworld_info*);
#endif

