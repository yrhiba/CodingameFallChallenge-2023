#include "header.hpp"

/*start*/
void	Game::setDronesDefaultFishesAndPriorityzFishes(void)
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
}

void	Game::dronesExploreFishesAndTheMap(void)
{
	if (this->game_turn==0)
	{
		this->setDronesDefaultFishesAndPriorityzFishes();
		for (int droneId:this->myDrones)
		{
			Drone &drone = this->getDroneById(droneId);
			drone.needToReachTargetPos = true;
			for (int fishId:this->typeFishes[2])
				if (drone.defaultFishesToScan.count(fishId))
				{
					drone.TargetPos = this->getFishById(fishId).estimationPosition;
					break;
				}
		}
	}
	for (int droneId:this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);
		vector<int> orderedFishes;
		for (int type=2; type>=0; type--)
			for (int fishId:this->typeFishes[type])
				if (drone.defaultFishesToScan.count(fishId) && this->getFishById(fishId).availlableToscan)
					orderedFishes.push_back(fishId);
		if (orderedFishes.empty())
		{
			drone.needToReachTargetPos = false;
			drone.TargetPos = EVector(0, 0);
			if (drone.scannedCreatures.size())
				drone.mustGoToTop = true;
		}
		else if (drone.needToReachTargetPos) continue;
		else
		{
			drone.assignedFishToScan = true;
			drone.TargetFishToScan = orderedFishes.front();
		}
	}
}


/*
first: assign a target position to reach
second: if the position is reach see the avillabilty to go top
		or tareget other fishes to scan or kick.

*/