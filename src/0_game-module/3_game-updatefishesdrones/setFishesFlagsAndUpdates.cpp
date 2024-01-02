#include "../includes/Game.hpp"

/*start*/

void Game::setFishesFlagsAndUpdates(void)
{
	for (Fish &fish : this->allFishes)
	{
		if (fish.type == -1) continue;

		if (fish.dead) continue;

		fish.setAvaillabilty();
		fish.extimatePossiblePosition();

		if (fish.availlableToscan)
		{
			this->fishsPossibleToScan.insert(fish.id);
			this->fishsPossibleToScanType[fish.type].insert(fish.id);
		}

		if (fish.availableToKick)
		{
			this->fishsPossibleToKick.insert(fish.id);
			this->fishsPossibleToKickType[fish.type].insert(fish.id);
		}
	}
}
