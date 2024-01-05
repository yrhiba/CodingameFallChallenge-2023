#include "header.hpp"

/*start*/

void	Game::droneLighEvaluateState(Drone &drone)
{
	if ((drone.battery < 5) || (this->game_turn < 5)
		|| (drone.mustGoToTop) || (drone.emergency) || (drone.assignedFishToKick))
	{
		drone.light = false;
		return ;
	}

	int	r = 3;

	// if (drone.needToReachTargetPos && calcDistance(drone.pos+drone.velocty, drone.TargetPos) < 1500)
	// {
	// 	r = 2;
	// }
	// else if ((drone.assignedFishToScan)
	// 	&& (calcDistance(drone.pos+drone.velocty, this->getFishById(drone.TargetFishToScan).estimationPosition) < 2000))
	// {
	// 	r = 2;
	// }

	drone.light = (this->game_turn%r==0);
}
