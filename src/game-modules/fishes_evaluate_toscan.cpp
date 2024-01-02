#include "../header.hpp"

/*start*/

void	Game::fishesEvaluatePossibleToScan(void)
{
	for (Fish &fish : this->allFishes)
	{
		// if ugly
		if (fish.type == -1) continue;
		// if it already out of the map
		if (fish.existZones.size() != 3) continue;
		// if i already scan it and saved
		if (fish.scannedByMe) continue;
		// if it already scanned inside one of my drones
		if (!(this->isDronesScannedByMeFish[fish.id].empty())) continue;
		// if it assigned to other drone
		if (!fish.availlableToscan) continue;

		// Add the fish to the list need to scan them.
		this->fishsPossibleToScan.insert(fish.id);
		this->fishsPossibleToScanType[fish.type].insert(fish.id);
	}
}
