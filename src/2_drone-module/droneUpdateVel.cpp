#include "header.hpp"

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

	if (targetFishToScan.visibleAtTurn != -1)
	{
		targetPos = targetFishToScan.pos + targetFishToScan.velocty;
	}
	else
	{
		targetPos = targetFishToScan.estimationPosition;
	}

	targetPos.y += (700 * ((drone.pos.y <= targetPos.y) ? -1 : +0.5));

	targetPos.roundme();

	drone.velocty = targetPos - drone.pos;
	drone.velocty.limit(drone.maxSpeed);
	drone.velocty.roundme();
}

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
		targetPos = targetFishToKick.pos + targetFishToKick.velocty;
		range = 1390;
	}
	else
	{
		targetPos = targetFishToKick.estimationPosition;
		range = 600;
	}

	targetPos.x += (range * ((targetPos.x < 5e3) ? 1 : -1));

	drone.velocty = targetPos - drone.pos;
	drone.velocty.limit(drone.maxSpeed);
	drone.velocty.roundme();
}

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
