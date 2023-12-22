#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	Actions actions;

	// this->debug();
	cerr << "turn: " << this->game_turn << endl;

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);

		actions.moveToPos(curDrone.pos.x, curDrone.pos.y, curDrone.battery >= 5 ? rand()%2 : 0);
	}

	return ;
}
