#include "../header.hpp"

/*start*/

void	Game::droneUpdateVelToScanTheTargetFish(Drone &drone)
{
	if (!(drone.assignedFishToScan) || drone.emergency)
	{
		cerr << "droneId: " << drone.id << " Not assigned to scan any fish." << endl;
		return ;
	}

	Fish &targetFishToScan = this->getFishById(drone.TargetFishToScan);

	EVector	targetPos;

	if (targetFishToScan.isVisible)
	{
		targetPos = targetFishToScan.pos;
	}
	else
	{
		targetPos = targetFishToScan.estimationPosition;
	}

	targetPos.y += (700 * ((drone.pos.y <= targetPos.y) ? -1 : +0.5));

	targetPos.roundme();

	drone.velocty = targetPos - drone.pos;
	drone.velocty.setMag(drone.maxSpeed);
	drone.velocty.roundme();
}

/*
future updates:
	-	add wait cases when the motor maybe kick the fish
		out of the map.
	- control light battery saver if i am way far from the fish
		and start lighting when i am close to a target
*/

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
				double	curDistance = calcDistance((fish.isVisible ? fish.pos : fish.estimationPosition), drone.pos);
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
				double	curDistance = calcDistance((fish.isVisible ? fish.pos : fish.estimationPosition), drone.pos);
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


// (maybe) || TODO: Evaluat the logic of that functiocn
// this function is just for learn and debug purpos it not take part with the final strategie
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
