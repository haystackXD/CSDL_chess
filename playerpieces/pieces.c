#include "pieces.h"

struct playerTextures *load_players_texture(struct gameworld_info *game)
{
	struct playerTextures *pTexture = safe_alloc(sizeof(struct playerTextures));
	struct texture tmpObj;

	const char *fname[] = {
		"images/whiteQueen.png", "images/whiteKing.png", "images/whiteRook.png",
		"images/whitePawn.png", "images/whiteBishop.png", "images/whiteKnight.png",
		"images/blackQueen.png", "images/blackKing.png", "images/blackPawn.png",
		"images/blackRook.png", "images/blackBishop.png", "images/blackKnight.png"
	};


	for (unsigned size = 0, idx = 0; size < sizeof(struct playerTextures); size += sizeof(SDL_Texture *), idx++)
	{
		texture_loadTextureFromFile(&tmpObj, game, fname[idx]);
		*(uint64_t *)((char *)pTexture+size) = (uint64_t)tmpObj.m_Texture;
	}
	return pTexture;
}


void destroy_playerTextures(struct playerTextures* self) 
{
	for (unsigned size = 0; size < sizeof(struct playerTextures); size += sizeof(SDL_Texture *))
		SDL_DestroyTexture((SDL_Texture *)((char *)self+size));
}

