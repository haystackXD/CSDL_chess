#ifndef _PAWN_PIECE_
#define _PAWN_PIECE_ 1
#include "../include/utils.h"

#include "pieces.h"
#include "../Texture.h"

void pawn_init(struct piece_struct *, SDL_Texture*, const int, const int);
void pawn_update_position(struct piece_struct *);


#endif

