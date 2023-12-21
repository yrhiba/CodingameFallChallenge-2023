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

	for (auto &droneId : this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);
		Fish &fish = this->allFishes.front();

		// cerr << drone << endl;
		// cerr << fish << endl;

		pair<int, int> vec = {(rand() % 2 ? 1 : -1), (rand() % 2 ? 1 : -1)};

		actions.moveToPos
		(
			fish.pos.x + (vec.first * 1e3),
			fish.pos.y + (vec.second * 1e3),
			drone.battery >= 5
		);
	}

	return ;
}
