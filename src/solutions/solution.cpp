#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"

/*start*/

void Game::solution()
{
	// this->debug();

	for (auto &droneId : this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);

		cerr << drone << endl;

		cout << "WAIT 0 That's Work Fine" << endl;
	}
}
