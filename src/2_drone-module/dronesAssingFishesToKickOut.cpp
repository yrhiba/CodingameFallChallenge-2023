#include "header.hpp"

/*start*/

// this function is just for learn and debug purpos it not take part with the final strategie
void	Game::dronesAssingFishesToKickOut(void)
{

	for (Fish &fish : this->allFishes)
	{
		if (fish.type == -1) continue;
		if (fish.dead) continue;
		if (!fish.availableToKick) continue;


	}
}

