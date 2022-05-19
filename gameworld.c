#include "gameworld.h"

void init_gameworld(struct gameworld_info *self)
{
	self->GAMENAME = "Chess Game";

	self->screen_width = SCREEN_WIDTH;
	self->screen_height = SCREEN_HEIGHT;

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

	self->gWindow = SDL_CreateWindow(
			self->GAMENAME, 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			self->screen_width, self->screen_height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
			);

	if (self->gWindow == NULL)
		debug_log("Could not create window SDL_Error: %s\n", SDL_GetError());

	// Create renderer device  to draw texture on
	self->gRenderer = SDL_CreateRenderer(
			self->gWindow,
			-1, 				// get first device
			SDL_RENDERER_ACCELERATED	// uses hardware acceleration
			);

	if (self->gRenderer == NULL)
		debug_log("No driver is present for rendering texture SDL_Error: %s\n", 
				SDL_GetError());
}


// Event driven game 
void handleEvent(struct gameworld_info *self)
{
	SDL_Event e;

	while (SDL_WaitEvent(&e) != 0)
	{
		switch (e.type)
		{
			case SDL_QUIT:
				return;
			default:
				break;
		}
		render(self);
	}
}

SDL_Rect mRect = {
	.x = 0,
	.y = 0,
	.w = 100,
	.h = 300,
};

void render(struct gameworld_info *self)
{
	/* Select the color for drawing. It is set to red here. */
	SDL_SetRenderDrawColor(self->gRenderer, 255, 0, 0, 255);

	// Clear renderer 
	SDL_RenderClear(self->gRenderer);
	SDL_SetRenderDrawColor(self->gRenderer, 0xff, 0xff, 0xff, 0xff);

	// Draw rectangle of blackcolor
	SDL_RenderDrawRect(self->gRenderer, &mRect);

	// Update Renderer 
	SDL_RenderPresent(self->gRenderer);
}

void run_mainloop(struct gameworld_info *self)
{
	// event driven application main loop
	handleEvent(self);
}

void free_gameworld(struct gameworld_info *self)
{
	// Destroy Renderer device
	SDL_DestroyRenderer(self->gRenderer);

	// Destory game window
	SDL_DestroyWindow(self->gWindow);

	// free SDL allocated data
	SDL_Quit();
}


int getWidth(struct gameworld_info* self)
{
	// returns window width
	return self->screen_width;
}

int getHeight(struct gameworld_info* self)
{
	// return window height
	return self->screen_height;
}
