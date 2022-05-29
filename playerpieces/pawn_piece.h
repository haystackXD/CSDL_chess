#ifndef _PAWN_PIECE_H_
#define _PAWN_PIECE_H_ 1

#include "../include/utils.h"
#include "../Actors.h"
#include "piece_interface.h"
#include "../Texture.h"

void pawn_init(struct piece_struct *, 
        SDL_Texture *, 
        const int, 
        const int);

void pawn_render(struct piece_struct *, struct gameworld_info *);
void pawn_update_position(struct piece_struct *, void *[], int, int);

#endif

