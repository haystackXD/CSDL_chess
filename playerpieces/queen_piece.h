#ifndef __QUEEN_PIECE_H_
#define __QUEEN_PIECE_H_ 1

#include "../include/utils.h"
#include "piece_interface.h"
#include "../Texture.h"

void queen_init(struct piece_struct *, SDL_Texture *, const int, const int);
void queen_render(struct piece_struct *, struct gameworld_info *);

#endif
