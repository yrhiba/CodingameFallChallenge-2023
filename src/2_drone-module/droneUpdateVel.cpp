#include "header.hpp"

/*start*/

void Game::droneUpdateVel(Drone &drone)
{
	// must go to kick a fish out of the map : Highest Priority
	if (drone.assignedFishToKick)
	{
		drone.action.setMsg("Kick-Fish-" + to_string(drone.TargetFishToKick));
		this->droneUpdateVelToKickOutTheTargetFish(drone);
	}
	// must go to scan a fish : Second Priority
	else if (drone.assignedFishToScan)
	{
		drone.action.setMsg("Scan-Fish-" + to_string(drone.TargetFishToScan));
		this->droneUpdateVelToScanTheTargetFish(drone);
	}
	// Go to save If Currently Sacnned fihes and don't have work to do
	else if (drone.scannedCreatures.size() > 0)
	{
		// move to Top
		drone.action.setMsg("Going-To-Save");
		drone.velocty = EVector(0, -600);
	}
	// must go to top | save the scanned fishes
	else
	{
		// Do Nothing
		drone.action.setMsg("Nothing-To-Do");
		drone.velocty = EVector(0, 0);
	}
}
