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

		// EXPLORE MODE

		curDrone.updatePos();
		curDrone.edges();

		actions.moveToPos(curDrone.pos.x, curDrone.pos.y, curDrone.light);
	}

	return ;
}
