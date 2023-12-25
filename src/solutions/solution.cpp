#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	Actions actions;

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);

		if (this->game_turn == 0)
		{
			EVector gravity = EVector(1000, 1000);
			gravity.setMag(curDrone.maxSpeed);
			curDrone.applyForce(gravity);
		}

		curDrone.updatePos();
		curDrone.edges();

		if (this->game_turn > 4 && curDrone.battery >= 5)
		{
			curDrone.light = (this->game_turn % 2) ? 1 : 0;
		}

		actions.moveToPos(
			curDrone.pos.x,
			curDrone.pos.y,
			curDrone.light
		);
	}

	return ;
}
