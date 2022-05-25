#include "pawn.h"

void initPawns(struct pawn_struct *self, struct gameworld_info* game)
{
	texture_loadTextureFromFile(&self->m_Piece[0], game, "images/blackPawn.png");
}
