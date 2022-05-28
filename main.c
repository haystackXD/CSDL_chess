#include "include/utils.h"
#include "GameWorld.h"


int main(int argc, char *argv[])
{
	struct gameworld_info chessgame;

	// initialize window, necessary structs
	init_gameworld(&chessgame);

	// game main loop
	run_mainloop(&chessgame);

	// free allocated game memory
	free_gameworld(&chessgame);

	return 0;
}
