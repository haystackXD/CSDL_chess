#ifndef GAME_PIECE
#define GAME_PIECE 1

#define TOTAL_CHESS_COLS 8
#define TOTAL_CHESS_ROWS 8
#define TOTAL_CHESS_SQUARES (TOTAL_CHESS_COLS * TOTAL_CHESS_ROWS)

enum Type {
    NONE,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    KING,
    QUEEN
};

#define TYPE_COUNT  6
#define COLOR_COUNT 2

enum Color {
    BLACK,
    WHITE
};

struct Piece {
    enum Type type;
    enum Color color;
};

struct piece_stack{
    unsigned char buffer[0xff];
    int top;
};



void setupBoard(struct Piece*, int);
/*
*/
void piece_getMoves(struct Piece *, struct piece_stack*, int, int);
#endif
