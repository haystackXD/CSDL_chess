#include "GameWorld.h"
#include "Actors.h"

void init_gameworld(struct gameworld_info *self)
{
	self->GAMENAME = "Chess Game";

	self->screen_width = SCREEN_WIDTH;
	self->screen_height = SCREEN_HEIGHT;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)              // Initialize SDL2
		debug_log("SDL could not able initialize SDL_Error: %s\n", SDL_GetError());


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

	int img_flags = IMG_INIT_PNG;

	// Initialize SDL_image for png
	if ((IMG_Init(img_flags) & IMG_INIT_PNG) != img_flags)
		debug_log("SDL_image could not initialize SDL_Error: %s\n", SDL_GetError());

	// return Actors required by the game
	self->iActors = createActors(self);
}


// Handle events for game window
void handleEvent(struct gameworld_info *self, SDL_Event* e)
{
	if (e->window.event == SDL_WINDOWEVENT_RESIZED)
	{
		self->screen_width = e->window.data1;
		self->screen_height = e->window.data2;
	}

}

// Render textures on screen
void render(struct gameworld_info *self)
{
	struct ActorCollector *gameActors = (struct ActorCollector *)self->iActors;

	/* Select the color for drawing. It is set to red here. */
	SDL_SetRenderDrawColor(self->gRenderer, 0xaf, 0xdf, 0xfd, 0xff);

	// Clear renderer 
	SDL_RenderClear(self->gRenderer);

	// Render all actors
	renderActors(gameActors, self);

	// Update Renderer 
	SDL_RenderPresent(self->gRenderer);
}

void run_mainloop(struct gameworld_info *self)
{
    struct ActorCollector* iactors = (struct ActorCollector *)self->iActors;
	SDL_Event e;
	self->fw_cursor = false;
    SDL_Rect *m_Rect = &iactors->chessBoxObj.m_Rect;
    struct piece_struct *mypiece = NULL;
    int row, col;

	while (SDL_WaitEvent(&e) != 0)
	{
		switch (e.type)
		{
			// Quit game loop
			case SDL_QUIT:
				return;

				// Handle window events
			case SDL_WINDOWEVENT:
				handleEvent(self, &e);
				break;

			case SDL_MOUSEMOTION:
                 if (
                         m_Rect->x < e.motion.x &&
                         m_Rect->y < e.motion.y &&
                         m_Rect->x + m_Rect->w > e.motion.x &&
                         m_Rect->y + m_Rect->h > e.motion.y
                 )
                 {
                     row = (e.motion.y - m_Rect->y) / (m_Rect->h / 8);
                     col = (e.motion.x - m_Rect->x) / (m_Rect->w / 8);

                     if (mypiece != NULL)
                        mypiece->pinterface->update_position(mypiece, iactors->boxes, row, col);
                 }

				break;

			case SDL_MOUSEBUTTONUP:
                 if (
                         m_Rect->x < e.motion.x &&
                         m_Rect->y < e.motion.y &&
                         m_Rect->x + m_Rect->w > e.motion.x &&
                         m_Rect->y + m_Rect->h > e.motion.y
                 )
                 {
                     row = (e.motion.y - m_Rect->y) / (m_Rect->h / 8);
                     col = (e.motion.x - m_Rect->x) / (m_Rect->w / 8);

                     if (iactors->boxes[row * 8 + col] != NULL)
                         mypiece = iactors->boxes[row * 8 +col];

                     self->fw_cursor = !self->fw_cursor;
                     if (self->fw_cursor == false)
                         mypiece = NULL;
                 }
				break;
		}

		render(self);
	}
}

void free_gameworld(struct gameworld_info *self)
{
	// Free Actors before closing game
	free(self->iActors);

	// Destroy Renderer device
	SDL_DestroyRenderer(self->gRenderer);

	// Destory game window
	SDL_DestroyWindow(self->gWindow);

	// unload the dynamically loaded image libraries
	IMG_Quit();

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
