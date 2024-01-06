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
	// targetPos.y += (700 * ((drone.pos.y <= targetPos.y) ? -1 : +0.5));
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
	double	range = 0;
	if (targetFishToKick.visibleAtTurn != -1)
	{
		targetPos = targetFishToKick.pos + targetFishToKick.velocty;
		range = 800;
	}
	else
	{
		targetPos = targetFishToKick.estimationPosition;
	}
	targetPos.x += (range * ((targetPos.x < 5e3) ? 1 : -1));
	drone.velocty = targetPos - drone.pos;
	drone.velocty.limit(drone.maxSpeed);
	drone.velocty.roundme();
}

void Game::droneUpdateVel(Drone &drone)
{
	if (drone.mustGoToTop)
	{
		// move to Top
		drone.action.setMsg("Going-To-Top");
		drone.velocty = EVector(0, -600);
	}
	// must go to kick a fish out of the map : Highest Priority
	else if (drone.assignedFishToKick)
	{
		drone.action.setMsg("Kick-Fish-" + to_string(drone.TargetFishToKick));
		this->droneUpdateVelToKickOutTheTargetFish(drone);
	}
	else if (drone.needToReachTargetPos)
	{
		drone.action.setMsg("Explore-Fishes");
		drone.velocty = drone.TargetPos - drone.pos;
		drone.velocty.limit(drone.maxSpeed);
		drone.velocty.roundme();
		if (drone.velocty.isZero()) drone.action.message += "Bad-Move";
	}
	// must go to scan a fish : Second Priority
	else if (drone.assignedFishToScan)
	{
		drone.action.setMsg("Scan-Fish-" + to_string(drone.TargetFishToScan));
		this->droneUpdateVelToScanTheTargetFish(drone);
	}
	// Go to save If Currently Sacnned fihes and don't have work to do
	else
	{
		// move to Top
		drone.action.setMsg("Going-To-Top");
		EVector target = EVector(drone.pos.x, 500);
		drone.velocty = target - drone.pos;
		drone.velocty.limit(drone.maxSpeed);
		drone.velocty.roundme();
		if (drone.velocty.isZero())	drone.action.setMsg("Satying-Save");
	}
}
