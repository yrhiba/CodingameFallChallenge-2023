#include "header.hpp"

/*start*/

void	Game::droneLighEvaluateState(Drone &drone)
{
	if ((drone.battery < 5) || (this->game_turn < 5) || (drone.pos.y < 3000)
		|| (drone.mustGoToTop) || (drone.emergency) || (drone.assignedFishToKick))
	{
		drone.light = false;
		return ;
	}

	int	r = 3;

	if (drone.pos.y > 6500) r = 2;

	drone.light = (this->game_turn%r==0);
}
