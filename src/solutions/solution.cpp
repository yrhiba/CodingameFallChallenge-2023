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
		cerr << fish << endl << endl;

		EVector vect = drone.pos - fish.pos;

		vect.setMag(600);

		cerr << "vect: " << vect << " | " << vect.magnitude() << endl;

		actions.moveToPos
		(
			drone.pos.x + vect.x,
			drone.pos.y + vect.y,
			drone.battery >= 5
		);
	}

	return ;
}
