#include "../header.hpp"

/*start*/

void	Game::fishesEvaluatePossibleToScan(void)
{
	for (Fish &fish : this->allFishes)
	{
		if (!fish.availlableToscan) continue;

		// Add the fish to the list need to scan them.
		this->fishsPossibleToScan.insert(fish.id);
		this->fishsPossibleToScanType[fish.type].insert(fish.id);
	}
}
