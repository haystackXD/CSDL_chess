#include "scene1.h"
#include "scene2.h"

static void drawScene1(struct gameScene* self, struct winInfo* wInfo)
{
	struct scene1_objects* m_objects = self->private_data;

	SDL_SetRenderDrawColor(wInfo->gRenderer, 0, 0, 0xff, 0xff);
	SDL_RenderClear(wInfo->gRenderer);

	SDL_RenderCopy(wInfo->gRenderer, m_objects->chessTexture.m_Texture, NULL, NULL);
}

static void handleEvent1(struct gameScene* self, struct winInfo* winfo)
{
	SDL_Event* e = &winfo->e;
	if (e->type == SDL_KEYDOWN && (e->key.keysym.sym == SDLK_KP_ENTER || e->key.keysym.sym == SDLK_RETURN))
	{
		self->freeScene(self);
		self->initScene(self, winfo);
	}
}

static void freeScene1(struct gameScene* self)
{
	struct scene1_objects* m_objects = self->private_data;
	if (m_objects->chessTexture.m_Texture)
	{
		SDL_DestroyTexture(m_objects->chessTexture.m_Texture);
		m_objects->chessTexture.m_Texture = NULL;
	}
	free(self->private_data);
	self->private_data = NULL;
}

void initScene1(struct gameScene* self, struct winInfo* wInfo)
{
	struct scene1_objects* m_objects;

	m_objects = malloc(sizeof(struct scene1_objects));
	assert(m_objects != NULL);

	self->private_data = m_objects;
	self->initScene = initScene2;
	self->drawScene = drawScene1;
	self->handleEvent = handleEvent1;
	self->freeScene = freeScene1;

	loadTextureFromPath(&m_objects->chessTexture, wInfo->gRenderer, ".\\image\\chess.png");
}
