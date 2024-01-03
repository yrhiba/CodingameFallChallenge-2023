#include "header.hpp"

/*start*/

void Game::droneUpdateVel(Drone &drone)
{
	/*
		have the highest highest priority and if it true
		that mean that's the last mission that i need to do
		to win the game.
		set it true after evaluated the possibilty	of winning
		without wasting time with other missions 
	*/
	if (drone.mustGoToTop)
	{
		// move to Top
		drone.action.setMsg("Going-To-Win");
		drone.velocty = EVector(0, -600);
	}
	// must go to kick a fish out of the map : Highest Priority
	else if (drone.assignedFishToKick)
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
