#include "scene2.h"
#include "piece.h"

static void freeScene2(struct gameScene* self)
{
	struct scene2_objects* m_objects = self->private_data;

	// destroy all textures
	for (int idy = 0; idy < 2; idy++)
		for (int idx = 0; idx < 6; idx++)
			SDL_DestroyTexture(m_objects->p_Texture[idy * TYPE_COUNT + idx].m_Texture);

	free(self->private_data);
	self->private_data = NULL;
}

static void handleEvent2(struct gameScene* self, struct winInfo* winfo)
{
	SDL_Event* e = &winfo->e;
	switch (e->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			struct scene2_objects* m_objects = self->private_data;
			int idy, idx, boxSize;
			enum Color color;

			boxSize = m_objects->boardSize / 8;
			idx = (e->button.x - m_objects->start_x) / boxSize;
			idy = (e->button.y - m_objects->start_y) / boxSize;
 			color = (m_objects->mode & 0xffff0000) == 0x00 ? BLACK : WHITE;	// whose turn

			if (
				m_objects->moving_piece.type == NONE &&
				e->button.x > m_objects->start_x  && e->button.x < m_objects->start_x + m_objects->boardSize &&
				e->button.y > m_objects->start_y && e->button.y < m_objects->start_y + m_objects->boardSize &&
				m_objects->chessboard[idy * TOTAL_CHESS_COLS + idx].type != NONE &&
				m_objects->chessboard[idy * TOTAL_CHESS_COLS + idx].color != color
			)
			{

				register int fIndex = idy * TOTAL_CHESS_COLS + idx;
				m_objects->prev_position = fIndex;

				piece_getMoves(m_objects->chessboard,
					&m_objects->m_Stack, 
					fIndex,
					m_objects->mode);

				memcpy(&m_objects->moving_piece, &m_objects->chessboard[fIndex], sizeof(struct Piece));
				m_objects->chessboard[fIndex].type = NONE;
			}
		}
		break;

		case SDL_MOUSEBUTTONUP:
		{
			struct scene2_objects* m_objects = self->private_data;
			int idy, idx, boxSize;

			if (
				m_objects->moving_piece.type != NONE &&
				e->button.x > m_objects->start_x  && e->button.x < m_objects->start_x + m_objects->boardSize &&
				e->button.y > m_objects->start_y && e->button.y < m_objects->start_y + m_objects->boardSize
			)
			{
				boxSize = m_objects->boardSize / 8;
				idx = (e->button.x - m_objects->start_x) / boxSize;
				idy = (e->button.y - m_objects->start_y) / boxSize;
				int current_position = idy * TOTAL_CHESS_COLS + idx;

				// invalid move set piece to previous location
				struct piece_stack *m_Stack = &m_objects->m_Stack;
				bool flag = false;

				for (int idx = 0; idx < m_Stack->top; idx++)
				{
					if (m_Stack->buffer[idx] == current_position)
					{
						flag = true;
						break;
					}
				}
				!flag ?  current_position = m_objects->prev_position : m_objects->mode = ~m_objects->mode;

				// change position of selected piece
				memcpy(&m_objects->chessboard[current_position], &m_objects->moving_piece, sizeof(struct Piece));
				m_objects->moving_piece.type = NONE;
			}
		}
		break;
	}
}

static void drawScene2(struct gameScene* self, struct winInfo* winfo)
{
	struct scene2_objects *m_objects = self->private_data;

	m_objects->boardSize = MIN(winfo->width, winfo->height) / TOTAL_CHESS_COLS * TOTAL_CHESS_ROWS;
	m_objects->start_x = (winfo->width / 2) - (m_objects->boardSize / 2);			// balance across x
	m_objects->start_y = (winfo->height / 2) - (m_objects->boardSize / 2);			// balance across y

	int boxSize = m_objects->boardSize / TOTAL_CHESS_COLS;
	unsigned char color = 0xa0;
	SDL_Rect m_Rect = {
		.w = boxSize,
		.h = boxSize
	};

	SDL_SetRenderDrawColor(winfo->gRenderer, 0xff, 0xe4, 0xc4, 0xff);
	SDL_RenderClear(winfo->gRenderer);

	// render board
	for (int idy = 0; idy < TOTAL_CHESS_ROWS; idy++)
	{
		for (int idx = 0; idx < TOTAL_CHESS_COLS; idx++)
		{
			m_Rect.x = m_objects->start_x + idx * boxSize;
			m_Rect.y = m_objects->start_y + idy * boxSize;

			SDL_SetRenderDrawColor(winfo->gRenderer, color, color, color, 0xff);
			SDL_RenderFillRect(winfo->gRenderer, &m_Rect);

			register int bIndex = idy * TOTAL_CHESS_COLS + idx;
			if (m_objects->chessboard[bIndex].type != NONE)
			{
				SDL_RenderCopy(winfo->gRenderer, 
				m_objects->p_Texture[m_objects->chessboard[bIndex].color * TYPE_COUNT
				+ m_objects->chessboard[bIndex].type-1].m_Texture, 
				NULL,
				&m_Rect);
			}
			color = ~color;
		}
		color = ~color;
	}

	// render anymoving piece if there one
	if (m_objects->moving_piece.type != NONE) {
		struct piece_stack *m_Stack = &m_objects->m_Stack;

		SDL_SetRenderDrawBlendMode(winfo->gRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(winfo->gRenderer, 0xff, 0xff, 0x00, 0x20);
		for (int idx = 0; idx < m_Stack->top; idx++) {
			m_Rect.x = m_objects->start_x + (m_Stack->buffer[idx] % TOTAL_CHESS_ROWS) * boxSize;
			m_Rect.y = m_objects->start_y + (m_Stack->buffer[idx] / TOTAL_CHESS_COLS) * boxSize;

			SDL_RenderFillRect(winfo->gRenderer, &m_Rect);
		}

		// piece displayed in middle to mouse bar
		m_Rect.x = winfo->e.button.x - boxSize / 2;
		m_Rect.y = winfo->e.button.y - boxSize / 2;

		SDL_RenderCopy(
			winfo->gRenderer,
			m_objects->p_Texture[m_objects->moving_piece.color * TYPE_COUNT + m_objects->moving_piece.type-1].m_Texture,
			NULL,
			&m_Rect
		);

	}
}

void initScene2(struct gameScene* self, struct winInfo* winfo)
{
	struct scene2_objects *m_objects;
	int idx;

	m_objects = malloc(sizeof(struct scene2_objects));
	assert(m_objects != NULL);

	self->private_data = m_objects;
	self->handleEvent = handleEvent2;
	self->drawScene = drawScene2;
	self->freeScene = freeScene2;

	m_objects->mode = 0xffff0000;
	setupBoard(m_objects->chessboard , m_objects->mode);

	idx = 0;
	loadTextureFromPath(&m_objects->p_Texture[BLACK * TYPE_COUNT + idx++], winfo->gRenderer, "image/black_pawn.png");
	loadTextureFromPath(&m_objects->p_Texture[BLACK * TYPE_COUNT + idx++], winfo->gRenderer, "image/black_rook.png");
	loadTextureFromPath(&m_objects->p_Texture[BLACK * TYPE_COUNT + idx++], winfo->gRenderer, "image/black_knight.png");
	loadTextureFromPath(&m_objects->p_Texture[BLACK * TYPE_COUNT + idx++], winfo->gRenderer, "image/black_bishop.png");
	loadTextureFromPath(&m_objects->p_Texture[BLACK * TYPE_COUNT + idx++], winfo->gRenderer, "image/black_king.png");
	loadTextureFromPath(&m_objects->p_Texture[BLACK * TYPE_COUNT + idx++], winfo->gRenderer, "image/black_queen.png");

	idx = 0;
	loadTextureFromPath(&m_objects->p_Texture[WHITE * TYPE_COUNT + idx++], winfo->gRenderer, "image/white_pawn.png");
	loadTextureFromPath(&m_objects->p_Texture[WHITE * TYPE_COUNT + idx++], winfo->gRenderer, "image/white_rook.png");
	loadTextureFromPath(&m_objects->p_Texture[WHITE * TYPE_COUNT + idx++], winfo->gRenderer, "image/white_knight.png");
	loadTextureFromPath(&m_objects->p_Texture[WHITE * TYPE_COUNT + idx++], winfo->gRenderer, "image/white_bishop.png");
	loadTextureFromPath(&m_objects->p_Texture[WHITE * TYPE_COUNT + idx++], winfo->gRenderer, "image/white_king.png");
	loadTextureFromPath(&m_objects->p_Texture[WHITE * TYPE_COUNT + idx++], winfo->gRenderer, "image/white_queen.png");
}
