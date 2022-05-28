#ifndef _PLAYER_TEXTURE_H_
#define _PLAYER_TEXTURE_H_ 1

#include "../include/utils.h"
#include "../Texture.h"

struct playerTextures 
{
	SDL_Texture* whiteQueen;
	SDL_Texture* whiteKing;
	SDL_Texture* whiteRook;
	SDL_Texture* whitePawn;
	SDL_Texture* whiteBishop;
	SDL_Texture* whiteKnight;

	SDL_Texture* blackQueen;
	SDL_Texture* blackKing;
	SDL_Texture* blackPawn;
	SDL_Texture* blackRook;
	SDL_Texture* blackBishop;
	SDL_Texture* blackKnight;
};

// load player texture with required images
struct playerTextures *load_players_texture(struct gameworld_info *game);

// destroy player texture that is loaded during initialize-
// time 
void destroy_playerTextures(struct playerTextures* self);

#endif

