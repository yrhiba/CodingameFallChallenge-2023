#include "header.hpp"

/*start*/

void	Game::droneLighEvaluateState(Drone &drone)
{
	int visibleUglys = 0;
	int totalUglys = this->typeFishes[-1].size();
	for (int ulgyId : this->typeFishes[-1])
		visibleUglys+=(this->getFishById(ulgyId).visibleAtTurn!=-1);
	if (totalUglys == visibleUglys)
	{
		if (drone.assignedFishToKick)
		{
			drone.light = false;
			return ;
		}
		if (!drone.assignedFishToScan)
		{
			drone.light = false;
			return ;
		}
		for (int fishId : this->fishsPossibleToScan)
		{
			Fish &fish = this->getFishById(fishId);
			double curDis = calcDistance(fish.estimationPosition, drone.pos);
			if (curDis < 2200)
			{
				drone.light = true;
				return ;
			}
		}
		drone.light = false;
		return ;
	}
	else
	{
		if (this->game_turn > 4 && drone.battery >= 5 && drone.pos.y > 2500)
		{
			drone.light = ((rand()%10+1)%3==0);
		}
	}
}
