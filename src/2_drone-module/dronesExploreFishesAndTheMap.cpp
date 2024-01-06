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
		for (int droneId:this->myDrones)
		{
			Drone &drone = this->getDroneById(droneId);
			drone.TargetPos = EVector((drone.leftDrone?1500:8500), 7900);
			drone.needToReachTargetPos = true;
			drone.reachedTargetPos = false;
		}
	}
	else
	{
		this->setDronesDefaultFishesAndPriorityzFishes();

		for (int droneId:this->myDrones)
		{
			Drone &drone = this->getDroneById(droneId);

			if (drone.needToReachTargetPos) continue;
			if (drone.assignedFishToScan) continue;

			int		fishIdToScan = -1;
			double	distance = -1;

			if (drone.priorityzeFishesToScan.size())
				for (int type=2; type>=0; type--)
				{
					for (int fishId:this->typeFishes[type])
						if (drone.priorityzeFishesToScan.count(fishId)
							&& this->getFishById(fishId).availlableToscan)
						{
							fishIdToScan = fishId;
							break;
						}
					if (fishIdToScan != -1) break;
				}

			if (fishIdToScan == -1)
			{
				for (Fish &fish:this->allFishes)
				{
					double curDis = calcDistance(drone.pos, fish.estimationPosition);
					if ((fish.availlableToscan) && ((distance == -1) || (curDis < distance)))
					{
						fishIdToScan = fish.id;
						distance = curDis;
					}
				}
			}

			if (fishIdToScan != -1)
			{
				drone.assignedFishToScan = true;
				drone.TargetFishToScan = fishIdToScan;
				this->getFishById(fishIdToScan).availlableToscan = false;
			}
		}
	}
}
