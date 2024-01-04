#include "header.hpp"

/*start*/

void	Game::dronesAssingFishesToScan(void)
{
	for (int droneId:this->myDrones)
	{
		Drone	&drone=this->getDroneById(droneId);
		for (int fishId:this->fishsPossibleToScan)
		{
			Fish &fish=this->getFishById(fishId);
			if (fish.dead || fish.deadNextTurn
				|| !fish.availlableToscan) continue;
			bool isFishInTheLeft = 
				(((fish.visibleAtTurn==-1)?fish.estimationPosition.x:fish.pos.x)
					<= drone.pos.x);
			if (drone.leftDrone == isFishInTheLeft)
				drone.priorityzeFishesToScan.insert(fish.id);
		}
		if (this->game_turn==0) // Default fishes to scan for current Drone.
			for (int fishID:drone.priorityzeFishesToScan)
				drone.defaultFishesToScan.insert(fishID);
	}
	if (this->game_turn==0)
	{
		Drone &drone1=this->getDroneById(this->myDrones.front());
		Drone &drone2=this->getDroneById(this->myDrones.back());
		Drone &rDrone=(drone1.defaultFishesToScan.size()<drone2.defaultFishesToScan.size())
			? drone1:drone2;
		for (Fish &fish:this->allFishes)
		{
			if ((fish.type==-1) || !(fish.availlableToscan)) continue;
			if (!drone1.defaultFishesToScan.count(fish.id)
				&& !drone2.defaultFishesToScan.count(fish.id))
			{
				rDrone.defaultFishesToScan.insert(fish.id);
			}
		}
	}
	for (int droneId:this->myDrones)
	{
		Drone	&drone=this->getDroneById(droneId);
		int		fishToScan=-1;
		if (!(drone.priorityzeFishesToScan.empty()))
		{
			for (int type = 2; type >= 0; type--)
			{
				for (int fishId:this->typeFishes[type])
					if (drone.priorityzeFishesToScan.count(fishId))
					{
						fishToScan = fishId;
						break;
					}
				if (fishToScan != -1) break;
			}
		}
		if (fishToScan==-1 && drone.scannedCreatures.empty())
		{
			for (int type=2; type>=0; type--)
			{
				for (int fishId:this->typeFishes[type])
					if (this->getFishById(fishId).availlableToscan
						/*&& drone.defaultFishesToScan.count(fishId)*/)
					{
						fishToScan = fishId;
						break;
					}
				if (fishToScan != -1) break;
			}
		}
		if (fishToScan == -1) continue;
		drone.assignedFishToScan = true;
		drone.TargetFishToScan = fishToScan;
		this->getFishById(fishToScan).availlableToscan=false;
	}
}

