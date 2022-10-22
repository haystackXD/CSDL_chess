#include <stdio.h>
#include "global.h"
#include "gamedata.h"
#undef main


int main(int argc, char* argv[])
{
	struct gamestruct gState;
	startGame(&gState, "chess", 1324, 800);
	return 0;
}
