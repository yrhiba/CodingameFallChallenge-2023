#include "../header.hpp"

/*start*/

void	Game::droneUpdateVelToKickOutTheTargetFish(Drone &drone)
{
	if (!(drone.assignedFishToKick))
	{
		cerr << "droneId: " << drone.id << " Not assigned to kick out any fish." << endl;
		return ;
	}

	Fish &targetFishToKick = this->getFishById(drone.TargetFishToKick);

	EVector	targetPos;
	double	range;

	if (targetFishToKick.isVisible)
	{
		targetPos = targetFishToKick.pos;
		range = 1390;
	}
	else
	{
		targetPos = targetFishToKick.targetPointToScan;
		range = 600;
	}

	targetPos.x += (range * ((targetPos.x < 5e3) ? 1 : -1));

	drone.velocty = targetPos - drone.pos;
	drone.velocty.setMag(drone.maxSpeed);
	drone.velocty.roundme();
}

/*
futur updates:
-	add fish simulation when it is in my range
	for more optimazation and speed to kick it out
	of the map and for best usage of the light.
*/
