#ifndef GAMESCENE1
#define GAMESCENE1 1
#include "global.h"
#include "scene.h"
#include "texture.h"

struct scene1_objects {
	struct texture chessTexture;
};

void initScene1(struct gameScene*, struct winInfo*);
#endif
