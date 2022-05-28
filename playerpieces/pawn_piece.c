#include "pawn_piece.h"

const struct piece_interface pawn_piece_interface = {
	.update_position = pawn_update_postion;
	.destroy_piece   = pawn_destroy_position;
};

void pawn_init(struct piece_struct *self, struct gameworld_info* game)
{
	self->pinterface = &pawn_piece_interface;
}
