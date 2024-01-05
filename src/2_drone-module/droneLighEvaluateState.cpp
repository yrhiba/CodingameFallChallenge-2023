#include "header.hpp"

/*start*/

void	Game::droneLighEvaluateState(Drone &drone)
{
	// int visibleUglys = 0;
	// int totalUglys = this->typeFishes[-1].size();
	// for (int ulgyId : this->typeFishes[-1])
	// 	visibleUglys+=(this->getFishById(ulgyId).visibleAtTurn!=-1);
	// if (totalUglys == visibleUglys)
	// {
	// 	if (drone.assignedFishToKick)
	// 	{
	// 		drone.light = false;
	// 		return ;
	// 	}
	// 	if (!drone.assignedFishToScan)
	// 	{
	// 		drone.light = false;
	// 		return ;
	// 	}
	// 	for (int fishId : this->fishsPossibleToScan)
	// 	{
	// 		Fish &fish = this->getFishById(fishId);
	// 		double curDis = calcDistance(fish.estimationPosition, drone.pos);
	// 		if (curDis < 2200)
	// 		{
	// 			drone.light = true;
	// 			return ;
	// 		}
	// 	}
	// 	drone.light = false;
	// 	return ;
	// }

	if ((drone.battery < 5) || (this->game_turn < 5) || (drone.mustGoToTop) || (drone.emergency) || (drone.assignedFishToKick))
	{
		drone.light = false;
		return ;
	}

	int	r = 3;

	if (drone.needToReachTargetPos && calcDistance(drone.pos+drone.velocty, drone.TargetPos) < 1500)
	{
		r = 2;
	}
	else if ((drone.assignedFishToScan)
		&& (calcDistance(drone.pos+drone.velocty, this->getFishById(drone.TargetFishToScan).estimationPosition) < 2000))
	{
		r = 2;
	}

	drone.light = (this->game_turn%r==0);
}
