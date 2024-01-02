#include "header.hpp"

/*start*/

void	Game::droneLighEvaluateState(Drone &drone)
{
	if (this->game_turn > 4 && drone.battery >= 5 && drone.pos.y > 3000)
	{
		drone.light = (this->game_turn % 2) ? 1 : 0;
	}
}
