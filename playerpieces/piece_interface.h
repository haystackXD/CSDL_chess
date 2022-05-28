#include "pieces.h"


struct piece_interface {
	// renders piece 
	void (*render)(struct piece_struct *, struct gameworld_info*);

	// update position as per rules 
	void (*update_position)(struct piece_struct *);	// update position of current player 
};


