#include "../header.hpp"

/*start*/

void	Game::dronesAssingFishesToKickOut(void)
{
	vector<int> fishsToKick;

	for (Fish &fish : this->allFishes)
	{
		// if ugly
		if (fish.type == -1) continue;
		// if it already out of the map
		if (fish.existZones.size() != 3) continue;
		// if it assigned to other drone
		if (!fish.availableToKick) continue;
		// if it scanned and saved by opponets
		if (fish.scannedByOp) continue;
		// if it currently scanned by opponents drones
		if (!(this->isDronesScannedByOpFish[fish.id].empty())) continue;

		// Add the fish to the list need to kick them before the opponets scan them
		fishsToKick.push_back(fish.id);
	}


	
}
