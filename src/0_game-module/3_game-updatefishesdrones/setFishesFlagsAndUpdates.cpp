#include "Game.hpp"

/*start*/

void Game::setFishesFlagsAndUpdates(void)
{
	for (Fish &fish : this->allFishes)
	{
		fish.setAvaillabilty();
		fish.extimatePossiblePosition();

		if (fish.availlableToscan)
		{
			this->fishsPossibleToScan.insert(fish.id);
			this->fishsPossibleToScanType[fish.type].insert(fish.id);
		}
		if ((fish.visibleAtTurn != -1) && fish.availableToKick)
		{
			this->fishsPossibleToKick.insert(fish.id);
			this->fishsPossibleToKickType[fish.type].insert(fish.id);
		}
	}
}
