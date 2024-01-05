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
	// else
	if ((drone.battery < 5) || (this->game_turn < 5))
	{
		drone.light = false;
		return ;
	}

	if ((drone.velocty.y > 0) && (drone.pos.y + drone.velocty.y) > 7900)
	{
		drone.light = true;
	}
	else if (this->game_turn > 4 && drone.pos.y > 2500)
	{
		drone.light = (this->game_turn%3==0);
	}
}
