#include "../header.hpp"

/*start*/

void	Game::dronesAssingFishesToKickOut(void)
{
	vector<int> fishsPossibleToKick;

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

		// To add later ignore the unvisible fishes
		// ***********************
		// ***********************

		// Add the fish to the list need to kick them before the opponets scan them
		fishsPossibleToKick.push_back(fish.id);
	}

	if (fishsPossibleToKick.empty())
	{
		cerr << "no-availlable-fishs-to-kick" << endl << endl;
		return ;
	}

	// for assignement if drones more than fishes assigne each fish to the closest drone.
	if (this->myDrones.size() <= fishsPossibleToKick.size())
	{
		for (int droneId : this->myDrones)
		{
			Drone	&drone = this->getDroneById(droneId);
			int		fishResId = -1;
			int		fishResDis = -1;
			for (int fishId : fishsPossibleToKick)
			{
				Fish	&fish = this->getFishById(fishId);
				if (!fish.availableToKick) continue;
				double	curDistance = calcDistance((fish.isVisible ? fish.pos : fish.targetPointToScan), drone.pos);
				if (((fishResId == -1) || (curDistance < fishResDis)))
				{
					fishResId = fish.id;
					fishResDis = curDistance;
				}
			}
			if (fishResId == -1) break;
			Fish &fishRes = this->getFishById(fishResId);
			fishRes.availableToKick = false;
			drone.TargetFishToKick = fishRes.id;
			drone.assignedFishToKick = true;
		}
	}
	// reverse the logic.ma
	else
	{
		for (int fishId : fishsPossibleToKick)
		{
			Fish	&fish = this->getFishById(fishId);
			int		droneResId = -1;
			int		droneResDis = -1;
			for (int droneId : this->myDrones)
			{
				Drone &drone = this->getDroneById(droneId);
				if (drone.assignedFishToKick) continue;
				double	curDistance = calcDistance((fish.isVisible ? fish.pos : fish.targetPointToScan), drone.pos);
				if ((droneResId == -1) || (curDistance < droneResDis))
				{
					droneResId = drone.id;
					droneResDis = curDistance;
				}
			}
			if (droneResId == -1) break;
			Drone &droneRes = this->getDroneById(droneResId);
			fish.availableToKick = false;
			droneRes.TargetFishToKick = fishId;
			droneRes.assignedFishToKick = true;
		}
	}
}
