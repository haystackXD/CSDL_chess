#ifndef GAMESCENE
#define GAMESCENE 1
#include "global.h"
#include "gamedata.h"

#define DEFAULTSCENE { .initScene = initScene1 }

struct gameScene {
	void* private_data;			// private scene
	void* shared_data;

	void (*initScene)(struct gameScene*,struct winInfo*);
	void (*handleEvent)(struct gameScene*, struct winInfo*);		// handle window events
	void (*drawScene)(struct gameScene*, struct winInfo*);		// draw stuff
	void (*freeScene)(struct gameScene*);
};

#endif
