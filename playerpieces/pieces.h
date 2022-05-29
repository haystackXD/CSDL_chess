#ifndef _PIECES_H_
#define _PIECES_H_ 1

#include "../include/utils.h"
#include "../Texture.h"

struct piece_struct 
{
	struct piece_interface *pinterface;

	// contains texture and its dimensions
	// for particular piece
    SDL_Texture *m_Texture;

	// contains coordinates of piece in chess board
	int which_col;
	int which_row;
};

// Initialize piece with given property
void piece_init(
		struct piece_struct *, 
		struct piece_interface *,
		SDL_Texture *, 
		const int, 
		const int
		);


#endif
