#include "../header.hpp"

/*start*/

void		Game::fishesSimulation(void)
{
	for (Fish &fish : this->allFishes)
	{
		// if ugly skip it
		if (fish.type == -1) continue;

		// if fish not visible
		if (fish.visibleAtTurn != this->game_turn)
			fish.visibleAtTurn = -1;
	}
}
