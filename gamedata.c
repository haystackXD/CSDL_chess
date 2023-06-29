#include "gamedata.h"
#include "scene.h"
#include "scene1.h"


void default_fcn() { }

void initwin(struct winInfo* self, const char* gameName, int width, int height)
{
	self->width = width;
	self->height = height;
	self->WINDOW_NAME = (char*)gameName;


	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
       // Create an application window with the following settings:
	self->gWindow = SDL_CreateWindow(
			self->WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			self->width,
			self->height,
			SDL_WINDOW_SHOWN
			);

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (IMG_Init(flags) & flags != flags)
		errExit("Img_Init: %s\n", IMG_GetError());

	// Check that the window was successfully created
	if (!self->gWindow)
		errExit("Unable to create SDL window SDL_Error: %s\n", SDL_GetError());

	self->gRenderer = SDL_CreateRenderer(self->gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!self->gRenderer)
		errExit("Unable to create SDL Renderer SDL_Error: %s\n", SDL_GetError());
}

void dostuff(struct winInfo* self)
{
	struct gameScene gScene = DEFAULTSCENE;
	bool quit = false;

	gScene.initScene(&gScene, self);
	gScene.drawScene(&gScene, self);
	SDL_RenderPresent(self->gRenderer);
	while (SDL_WaitEvent(&self->e))
	{
		if (self->e.type == SDL_QUIT)
			break;
		gScene.handleEvent(&gScene, self);
		// for sdl_waitevent
		gScene.drawScene(&gScene, self);
		SDL_RenderPresent(self->gRenderer);
	}
	gScene.freeScene(&gScene);
}

void closewin(struct winInfo* self)
{
	// Destroy renderer
	SDL_DestroyRenderer(self->gRenderer);

	// Close and destroy the window
	SDL_DestroyWindow(self->gWindow);

	// Clean up 
	IMG_Quit();
	SDL_Quit();
}

void startGame(struct gamestruct* self, const char* gameName, int width, int height)
{
	// initialize window and other stuff necessary for drawing
	initwin(&self->wInfo, gameName, width, height);

	dostuff(&self->wInfo);

	// close window and other stuff
	closewin(&self->wInfo);
}
