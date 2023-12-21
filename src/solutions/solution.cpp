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

		EVector dronePos = drone.pos;
		EVector fishPos = fish.pos;

		fishPos -= dronePos;

		fishPos.normalize();
		fishPos *= 100;

		cerr << fishPos << " " << fishPos.magnitude() <<  endl;

		actions.moveToPos
		(
			drone.pos.x + fishPos.x,
			drone.pos.y + fishPos.y,
			drone.battery >= 5
		);
	}

	return ;
}
