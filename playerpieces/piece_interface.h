#ifndef __PIECE_INTERFACE_H_
#define __PIECE_INTERFACE_H_ 1

#include "pieces.h"

struct piece_interface {
	// update position as per rules 
	void (*update_position)(struct piece_struct *, void *[], int, int);	// update position of current player 
    void (*render)(struct piece_struct *, struct gameworld_info* game);
};

#endif
