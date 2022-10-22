#ifndef GAMEDATA
#define GAMEDATA 1
#include "global.h"

struct winInfo {
	SDL_Window* gWindow;		// window for rendering
	SDL_Renderer* gRenderer;	// renderer

	const char* WINDOW_NAME;	// contain name of the window

	SDL_Event e;

	int width;			// width of window
	int height;			// height of window
};

struct gamestruct {
	struct winInfo wInfo;
};

void startGame(struct gamestruct*, const char*, int, int);
void initwin(struct winInfo*, const char*, int, int);
void default_fcn();


#endif
