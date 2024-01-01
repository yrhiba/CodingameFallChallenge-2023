#include "../header.hpp"

/*start*/

void	Game::fishesEvaluatePossibleToKick(void)
{
	for (Fish &fish : this->allFishes)
	{
		// if ugly
		if (fish.type == -1) continue;
		// if it already out of the map
		if (fish.existZones.size() != 3) continue;
		// if it scanned and saved by opponets
		if (fish.scannedByOp) continue;
		// if it currently scanned by opponents drones
		if (!(this->isDronesScannedByOpFish[fish.id].empty())) continue;
		// if it assigned to other drone
		if (!fish.availableToKick) continue;

		// Add the fish to the list need to kick them before the opponets scan them
		this->fishsPossibleToKick.insert(fish.id);
	}
}
