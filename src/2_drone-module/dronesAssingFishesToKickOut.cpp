#include "header.hpp"

/*start*/

void	Game::droneUpdateVelToKickOutTheTargetFish(Drone &drone)
{
	if (!(drone.assignedFishToKick) || drone.emergency)
	{
		cerr << "droneId: " << drone.id << " Not assigned to kick out any fish." << endl;
		return ;
	}

	Fish &targetFishToKick = this->getFishById(drone.TargetFishToKick);

	EVector	targetPos;
	double	range;

	if (targetFishToKick.visibleAtTurn != -1)
	{
		targetPos = targetFishToKick.pos;
		range = 1390;
	}
	else
	{
		targetPos = targetFishToKick.estimationPosition;
		range = 600;
	}

	targetPos.x += (range * ((targetPos.x < 5e3) ? 1 : -1));

	drone.velocty = targetPos - drone.pos;
	drone.velocty.setMag(drone.maxSpeed);
	drone.velocty.roundme();
}

// this function is just for learn and debug purpos it not take part with the final strategie
void	Game::dronesAssingFishesToKickOut(void)
{
	for (int droneId : this->myDrones)
	{
		Drone	&drone = this->getDroneById(droneId);

		if (drone.assignedFishToKick)
		{
			if (!(this->fishsPossibleToKick.count(drone.TargetFishToKick)) || drone.emergency)
			{
				drone.assignedFishToKick = false;
				drone.TargetFishToKick = -1;
			}
			else
			{
				this->getFishById(drone.TargetFishToKick).availableToKick = false;
			}
		}
	}

	if (this->fishsPossibleToKick.empty())
	{
		cerr << "no-availlable-fishs-to-kick" << endl << endl;
		return ;
	}

	// for assignement if drones more than fishes assigne each fish to the closest drone.
	if (this->myDrones.size() <= this->fishsPossibleToKick.size())
	{
		for (int droneId : this->myDrones)
		{
			Drone	&drone = this->getDroneById(droneId);
			if (drone.assignedFishToKick || drone.emergency) continue;
			int		fishResId = -1;
			int		fishResDis = -1;
			for (int fishId : this->fishsPossibleToKick)
			{
				Fish	&fish = this->getFishById(fishId);
				if (!fish.availableToKick) continue;
				double	curDistance = calcDistance(((fish.visibleAtTurn != -1) ? fish.pos : fish.estimationPosition), drone.pos);
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
		for (int fishId : this->fishsPossibleToKick)
		{
			Fish	&fish = this->getFishById(fishId);
			if (!fish.availableToKick) continue;
			int		droneResId = -1;
			int		droneResDis = -1;
			for (int droneId : this->myDrones)
			{
				Drone &drone = this->getDroneById(droneId);
				if (drone.assignedFishToKick || drone.emergency) continue;
				double	curDistance = calcDistance(((fish.visibleAtTurn != -1) ? fish.pos : fish.estimationPosition), drone.pos);
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

