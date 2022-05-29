#include "queen_piece.h"

const struct piece_interface queen_piece_interface = {
    .render = queen_render,
};

void queen_init(struct piece_struct *self, SDL_Texture* m_Texture, 
        const int which_row,
        const int which_col)
{
    piece_init(self, (struct piece_interface *)&queen_piece_interface, m_Texture, which_row, which_col);
}

void queen_render(struct piece_struct *self, struct gameworld_info* game)
{
    struct texture* chessBox = (struct texture *)game->iActors;
    const int square_length = chessBox->m_Rect.w / 8;

}
