#include "pieces.h"

// Initialize piece required interface and
// other properties 
void piece_init(
		struct piece_struct *self
		struct piece_interface *pieceInterface, 
		SDL_Texture* m_Texture,
		const int which_row,
		const int which_col
		)
{
	self->pinterface = pieceInterface;
	self->m_Piece.m_Texture = m_Texture;

	self->which_row = which_row;
	self->which_col = which_col;
}
