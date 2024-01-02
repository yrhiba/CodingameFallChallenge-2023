#include "header.hpp"

/*start*/

void Game::droneUpdateVel(Drone &drone)
{
	// must go to scan a fish
	if (drone.assignedFishToScan)
	{
		drone.action.setMsg("Scan-Fish-" + to_string(drone.TargetFishToScan));
		this->droneUpdateVelToScanTheTargetFish(drone);
	}
	// go to save if i scan some fishes
	else if (drone.scannedCreatures.size() > 0)
	{
		// move to Top
		drone.action.setMsg("Going-To-Save");
		drone.velocty = EVector(0, -600);
	}
	// must go to kick a fish out of the map
	else if (drone.assignedFishToKick)
	{
		drone.action.setMsg("Kick-Fish-" + to_string(drone.TargetFishToKick));
		this->droneUpdateVelToKickOutTheTargetFish(drone);
	}
	// must go to top | save the scanned fishes
	else
	{
		// Do Nothing
		drone.action.setMsg("Wander-On-The-Map");
		drone.velocty = drone.wanderForce();
		drone.velocty.setMag(drone.maxSpeed);
		drone.velocty.roundme();
	}
}
