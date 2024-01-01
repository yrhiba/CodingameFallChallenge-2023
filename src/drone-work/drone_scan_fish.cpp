#include "../header.hpp"

/*start*/

void	Game::droneUpdateVelToScanTheTargetFish(Drone &drone)
{
	if (!(drone.assignedFishToScan))
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
		targetPos = targetFishToScan.targetPointToScan;
	}

	drone.velocty = targetPos - drone.pos;
	drone.velocty.setMag(drone.maxSpeed);
	drone.velocty.roundme();
}

// (maybe) || TODO: Evaluat the logic of that functiocn
// this function is just for learn and debug purpos it not take part with the final strategie
void	Game::dronesAssingFishesToScan(void)
{
}

