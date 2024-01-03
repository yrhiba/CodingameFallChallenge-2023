#include "header.hpp"

/*start*/

void	Game::dronesAssignFishToScanWithType(int fishesType)
{
	// for assignement if drones more than fishes assigne each fish to the closest drone.
	if (this->myDrones.size() <= this->fishsPossibleToScanType[fishesType].size())
	{
		for (int droneId : this->myDrones)
		{
			Drone	&drone = this->getDroneById(droneId);
			if (drone.assignedFishToScan || drone.emergency) continue;
			int		fishResId = -1;
			int		fishResDis = -1;
			for (int fishId : this->fishsPossibleToScanType[fishesType])
			{
				if (!(this->fishsPossibleToScan.count(fishId))) continue;
				Fish	&fish = this->getFishById(fishId);
				if (!fish.availlableToscan) continue;
				double	curDistance = calcDistance(((fish.visibleAtTurn != -1) ? fish.pos : fish.estimationPosition), drone.pos);
				if (((fishResId == -1) || (curDistance < fishResDis)))
				{
					fishResId = fish.id;
					fishResDis = curDistance;
				}
			}
			if (fishResId == -1) break;
			Fish &fishRes = this->getFishById(fishResId);
			fishRes.availlableToscan = false;
			drone.TargetFishToScan = fishRes.id;
			drone.assignedFishToScan = true;
		}
	}
	// reverse the logic.ma
	else
	{
		for (int fishId : this->fishsPossibleToScanType[fishesType])
		{
			Fish	&fish = this->getFishById(fishId);
			if (!fish.availlableToscan) continue;
			int		droneResId = -1;
			int		droneResDis = -1;
			for (int droneId : this->myDrones)
			{
				Drone &drone = this->getDroneById(droneId);
				if (drone.assignedFishToScan || drone.emergency) continue;
				double	curDistance = calcDistance(((fish.visibleAtTurn != -1) ? fish.pos : fish.estimationPosition), drone.pos);
				if ((droneResId == -1) || (curDistance < droneResDis))
				{
					droneResId = drone.id;
					droneResDis = curDistance;
				}
			}
			if (droneResId == -1) break;
			Drone &droneRes = this->getDroneById(droneResId);
			fish.availlableToscan = false;
			droneRes.TargetFishToScan = fishId;
			droneRes.assignedFishToScan = true;
		}
	}
}

void	Game::dronesAssingFishesToScan(void)
{
	for (int droneId : this->myDrones)
	{
		Drone	&drone = this->getDroneById(droneId);

		if (drone.assignedFishToScan)
		{
			if (!(this->fishsPossibleToScan.count(drone.TargetFishToScan)) || drone.emergency)
			{
				drone.assignedFishToScan = false;
				drone.TargetFishToScan = -1;
			}
			else
			{
				this->getFishById(drone.TargetFishToScan).availlableToscan = false;
			}
		}
	}

	if (this->fishsPossibleToScan.empty())
	{
		cerr << "no-availlable-fishs-to-scan" << endl << endl;
		return ;
	}

	for (int type = 2; type >= 0; type--)
	{
		dronesAssignFishToScanWithType(type);
	}
}
