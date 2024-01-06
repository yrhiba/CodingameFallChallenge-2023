#include "header.hpp"

/*start*/

void	Game::droneLighEvaluateState(Drone &drone)
{
	if ((drone.battery < 5) || (this->game_turn < 3) || (drone.pos.y < 3000)
		|| (drone.mustGoToTop) || (drone.emergency) || (drone.assignedFishToKick))
	{
		drone.light = false;
		return ;
	}


	drone.light = (this->game_turn%2);
}
