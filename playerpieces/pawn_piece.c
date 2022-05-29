#include "pawn_piece.h"

const struct piece_interface pawn_piece_interface = {
	.update_position = pawn_update_position,
    .render = pawn_render,
};

void pawn_init(struct piece_struct *self, 
        SDL_Texture* m_Texture, 
        const int which_row, 
        const int which_col)
{
    piece_init(self, (struct piece_interface *)&pawn_piece_interface, m_Texture, which_row, which_col);
}

void pawn_render(struct piece_struct* self, struct gameworld_info* game)
{
    struct texture* chessBox = &(((struct ActorCollector *)game->iActors)->chessBoxObj);
    const int square_length = chessBox->m_Rect.w / 8;
    SDL_Rect m_Rect;

    m_Rect.x = chessBox->m_Rect.x + square_length * self->which_col;
    m_Rect.y = chessBox->m_Rect.y + square_length * self->which_row;

    m_Rect.w = square_length;
    m_Rect.h = square_length;

    SDL_RenderCopy(game->gRenderer, self->m_Texture, NULL, &m_Rect);
}

void pawn_update_position(struct piece_struct *self, void *boxes[], int row, int col)
{
    boxes[self->which_row * 8 + self->which_col] = NULL;

    self->which_col = col;
    self->which_row = row;

    boxes[self->which_row * 8 + self->which_col] = (void *)self;
}
