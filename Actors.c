#include "Actors.h"

// allocate memory and initilize coordinates
struct ActorCollector *createActors(void) 
{
	struct ActorCollector* gameActors;

	// Allocate memory for game actors
	gameActors = safe_alloc(sizeof(struct ActorCollector));

	gameActors->mRect.x = 0;
	gameActors->mRect.y = 0;
	gameActors->mRect.w = 100;
	gameActors->mRect.h = 100;
}
