#ifndef GAMESCENE2
#define GAMESCENE2 1

#include "scene.h"
#include "texture.h"
#include "piece.h"

struct scene2_objects {
	int boardSize;
	int start_x, start_y;

	int prev_position;
	int mode;

	struct piece_stack m_Stack;
	struct Piece moving_piece;

	// our task is to do operation with maximum optimization
	struct texture p_Texture[COLOR_COUNT * TYPE_COUNT];
	struct Piece chessboard[TOTAL_CHESS_COLS * TOTAL_CHESS_ROWS];
};

void initScene2(struct gameScene* self, struct winInfo* wInfo);
#endif
