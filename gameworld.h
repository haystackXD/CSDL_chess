#include "include/header.h"
#include "Actors.h"

struct gameworld_info 
{
	// Collection of actors for rendering handling 
	// All textures 
	struct ActorCollector *Actors;

	// name of window that is gamename
	const char* GAMENAME;

	// window for rendering texture and handling different events
	SDL_Window* gWindow;

	// Render for rendering hardware textures
	SDL_Renderer* gRenderer;

	// Window dimensions
	int screen_width;
	int screen_height;

};

// Initialize game world, window, render and
// set name for SDL_window 
void init_gameworld(struct gameworld_info *);

// main loop for application
void run_mainloop(struct gameworld_info *);

// Free game window and destroy other allocated
// data for the current window
void free_gameworld (struct gameworld_info *);

// Get window width;
int getWidth(struct gameworld_info *);

// Get window height
int getHeight(struct gameworld_info *);

// renders world onto main window
void render(struct gameworld_info *);

// handle SDL events 
void handleEvent(struct gameworld_info *);
