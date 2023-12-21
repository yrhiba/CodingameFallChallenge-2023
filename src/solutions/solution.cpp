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

		cerr << drone << endl;
		cerr << fish << endl;

		actions.moveToPos(fish.x, fish.y, drone.battery >= 5);
	}
}
