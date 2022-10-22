#include "global.h"
#include "piece.h"

int pos[] = {-1, 1};
int row, col, position;

void rook_moves(struct Piece* chessboard, struct piece_stack *m_Stack, int side_param)
{
    int idx, idy;
    // 
    for (idy = 0; idy < array_size(pos); idy++)
    {
        // do not repeat ourself
        for (idx = pos[idy]; row+side_param*idx < TOTAL_CHESS_ROWS && row+side_param*idx >= 0; idx += pos[idy])
        {
            if (chessboard[(row+side_param * idx) * TOTAL_CHESS_COLS + col].type == NONE)                           
                m_Stack->buffer[m_Stack->top++] = (row+side_param * idx) * TOTAL_CHESS_COLS + col;                  
            else                                                                                                    
            {                                                                                                       
        // most be enemy
                if (chessboard[(row+side_param * idx) * TOTAL_CHESS_COLS + col].color != chessboard[position].color)
                    m_Stack->buffer[m_Stack->top++] = (row+side_param * idx) * TOTAL_CHESS_COLS + col;              
                break;                                                                                              
            }                                                                                                       
        }

        // travere through all column
        for (idx = pos[idy]; col+idx < TOTAL_CHESS_COLS && col+idx >= 0; idx += pos[idy])
        {
            if (chessboard[row * TOTAL_CHESS_COLS + col+idx].type == NONE)                              
                m_Stack->buffer[m_Stack->top++] = row * TOTAL_CHESS_COLS + col+idx;                     
            else {                                                                                      
        // most be enemy
                if (chessboard[row * TOTAL_CHESS_COLS + col+idx].color != chessboard[position].color)   
                    m_Stack->buffer[m_Stack->top++] = row * TOTAL_CHESS_COLS + col+idx;                 
                break;                                                                                  
            }                                                                                           
        }
    }
}

#define _DIAGONAL(idy, idx) do {                                                                                \
    register int index = (row+idy) * TOTAL_CHESS_COLS + col+idx;                                     \
    if (chessboard[index].type == NONE || chessboard[index].color != chessboard[position].color)                \
        m_Stack->buffer[m_Stack->top++] = (row+idy) * TOTAL_CHESS_COLS + col+idx;                    \
} while (0)

#define DIAGONAL_UPDATE_WFOR(idy, idx) {                                                                        \
    if (chessboard[(row+idy) * TOTAL_CHESS_COLS + col+idx].type == NONE)                             \
        m_Stack->buffer[m_Stack->top++] = (row+idy) * TOTAL_CHESS_COLS + col+idx;                    \
    else if (chessboard[(row+idy) * TOTAL_CHESS_COLS + col+idx].color != chessboard[position].color) \
    {                                                                                                           \
        m_Stack->buffer[m_Stack->top++] = (row+idy) * TOTAL_CHESS_COLS + col+idx;                    \
        break;                                                                                                  \
    }                                                                                                           \
}

void bishop_moves(struct Piece* chessboard, struct piece_stack* m_Stack, int side_param)
{
    int idx, idy;

    //y = mx + c
    for (idx = 1, idy = -1; row+idx < TOTAL_CHESS_ROWS && col+idy >= 0; idx++, idy--)
        DIAGONAL_UPDATE_WFOR(idx, idy);

    for (idx = -1, idy = -1; row+idx >= 0 && col+idy >= 0; idx--, idy--)
        DIAGONAL_UPDATE_WFOR(idx, idy);

    for (idx = -1, idy = 1; row+idx >= 0 && col+idy < TOTAL_CHESS_COLS; idx--, idy++)
        DIAGONAL_UPDATE_WFOR(idx, idy);

    for (idx = 1, idy = 1; row+idx < TOTAL_CHESS_ROWS && col+idy < TOTAL_CHESS_COLS; idx++, idy++)
        DIAGONAL_UPDATE_WFOR(idx, idy);
}

void knight_moves(struct Piece* chessboard, struct piece_stack* m_Stack, int side_param)
{
    if (row+2 < TOTAL_CHESS_ROWS && col+1 < TOTAL_CHESS_COLS)
        _DIAGONAL(2, 1);

    if (row+1 < TOTAL_CHESS_ROWS && col+2 < TOTAL_CHESS_COLS)
        _DIAGONAL(1, 2);

    if (row-2 >= 0 && col+1 < TOTAL_CHESS_COLS)
        _DIAGONAL(-2, 1);

    if (row-1 >= 0 && col+2 < TOTAL_CHESS_COLS)
        _DIAGONAL(-1, 2);
    
    if (row-2 >= 0 && col-1 >= 0)
        _DIAGONAL(-2, -1);

    if (row-1 >= 0 && col-2 >= 0)
        _DIAGONAL(-1, -2);

    if (row+2 < TOTAL_CHESS_COLS && col-1 >= 0)
        _DIAGONAL(2, -1);

    if (row+1 < TOTAL_CHESS_COLS && col-2 >= 0)
        _DIAGONAL(1, -2);
}

void piece_getMoves(struct Piece* chessboard, struct piece_stack* m_Stack, int cur_position, int mode)
{
    int idx, side_param;

    position = cur_position;
    row = position / TOTAL_CHESS_ROWS;
    col = position % TOTAL_CHESS_COLS;

    side_param = (mode & 0xffff == 0xffff) ? -1 : 1;
    m_Stack->top = 0;

    switch (chessboard[position].type) 
    {
        case PAWN:
        {
            // it's first move
            idx = 0;
            if ((side_param == 1 && (row + side_param * idx) == 1) || (side_param == -1 && (row + side_param * idx) == 6))
            {
                for (idx = 1; idx < 3; idx++)
                    if (chessboard[(row+side_param*idx) * TOTAL_CHESS_COLS + col].type == NONE)
                        m_Stack->buffer[m_Stack->top++] = (row+side_param*idx) * TOTAL_CHESS_COLS + col;
            }

            // check for any possible members diagonal position
            if (((col+1) + side_param) < TOTAL_CHESS_COLS)
            {
                if (
                    chessboard[(row+side_param) * TOTAL_CHESS_COLS + col+1].type != NONE && 
                    chessboard[(row+side_param) * TOTAL_CHESS_COLS + col+1].color != chessboard[position].color
                )
                    m_Stack->buffer[m_Stack->top++] = (row+side_param) * TOTAL_CHESS_COLS + col+1;
            }

            if (((col-1) + side_param) >= 0)
            {
                if (
                    chessboard[(row+side_param) * TOTAL_CHESS_COLS + col-1].type != NONE && 
                    chessboard[(row+side_param) * TOTAL_CHESS_COLS + col-1].color != chessboard[position].color
                )
                    m_Stack->buffer[m_Stack->top++] = (row+side_param) * TOTAL_CHESS_COLS + col-1;
            }

            // check whether some piece is front of pawn
            if (chessboard[(row+side_param) * TOTAL_CHESS_COLS + col].type == NONE)
                    m_Stack->buffer[m_Stack->top++] = (row+side_param) * TOTAL_CHESS_COLS + col;
        }
        break;

        case QUEEN:
            rook_moves(chessboard, m_Stack, side_param);
            bishop_moves(chessboard, m_Stack, side_param);
        break;

        case ROOK:
            rook_moves(chessboard, m_Stack, side_param);
        break;

        case BISHOP:
            bishop_moves(chessboard, m_Stack, side_param);
        break;

        case KNIGHT:
            knight_moves(chessboard, m_Stack, side_param);
        break;
    }
}

static void printChess(struct Piece chessboard[])
{
    for (int idy = 0; idy < TOTAL_CHESS_ROWS; idy++)
    {
        for (int idx = 0; idx < TOTAL_CHESS_ROWS; idx++)
        {
            switch (chessboard[idy * TOTAL_CHESS_COLS + idx].color)
            {
                case BLACK:     printf("B"); break;
                case WHITE:     printf("W"); break;
                default:        printf("N"); break;
            }
            switch (chessboard[idy * TOTAL_CHESS_COLS + idx].type)
            {
                case NONE:      printf("N"); break;
                case PAWN:      printf("P"); break;
                case BISHOP:    printf("B"); break;
                case KNIGHT:    printf("K"); break;
                case ROOK:      printf("R"); break;
                case QUEEN:     printf("Q"); break;
                case KING:      printf("K"); break;
            }
            printf(" ");
        }
        printf("\n");
    }
}


void setupBoard(struct Piece*chessboard, int mode)
{
    int idx, side_param;
    side_param = (mode & 0xffff == 0x00) ? -1 : 1;

    if (side_param == 1)
    {
        for (idx = 0; idx < TOTAL_CHESS_COLS; idx++)
        {
            chessboard[0 * TOTAL_CHESS_COLS + idx].color = chessboard[1 * TOTAL_CHESS_COLS + idx].color = BLACK;
            chessboard[6 * TOTAL_CHESS_COLS + idx].color = chessboard[7 * TOTAL_CHESS_COLS + idx].color = WHITE;
        }
    }
    else if (side_param == -1) 
    { 
        for (idx = 0; idx < TOTAL_CHESS_COLS; idx++)
        {
            chessboard[0 * TOTAL_CHESS_COLS + idx].color = chessboard[1 * TOTAL_CHESS_COLS + idx].color = WHITE;
            chessboard[6 * TOTAL_CHESS_COLS + idx].color = chessboard[7 * TOTAL_CHESS_COLS + idx].color = BLACK;
        }
    }

    for (idx = 0; idx < TOTAL_CHESS_COLS; idx++)
    {
        chessboard[1 * TOTAL_CHESS_COLS + idx].type = PAWN;
        chessboard[6 * TOTAL_CHESS_COLS + idx].type = PAWN;
    }

    idx = 0;
    chessboard[0 * TOTAL_CHESS_COLS + idx].type = ROOK;
    chessboard[7 * TOTAL_CHESS_COLS + idx].type = ROOK;
    chessboard[0 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = ROOK;
    chessboard[7 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = ROOK;

    ++idx;
    chessboard[0 * TOTAL_CHESS_COLS + idx].type = KNIGHT;
    chessboard[7 * TOTAL_CHESS_COLS + idx].type = KNIGHT;
    chessboard[0 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = KNIGHT;
    chessboard[7 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = KNIGHT;

    ++idx;
    chessboard[0 * TOTAL_CHESS_COLS + idx].type = BISHOP;
    chessboard[7 * TOTAL_CHESS_COLS + idx].type = BISHOP;
    chessboard[0 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = BISHOP;
    chessboard[7 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = BISHOP;

    ++idx;
    chessboard[0 * TOTAL_CHESS_COLS + idx].type = KING;
    chessboard[7 * TOTAL_CHESS_COLS + idx].type = KING;
    chessboard[0 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = QUEEN;
    chessboard[7 * TOTAL_CHESS_COLS + (TOTAL_CHESS_COLS-idx-1)].type = QUEEN;

    printChess(chessboard);
}