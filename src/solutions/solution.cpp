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

	EVector vect1(100, 100), vect2(200, 200);

	cerr << vect1 << " " << vect2 << endl;
	
	vect1 += vect2;

	cerr << vect1 << endl;

	for (auto &droneId : this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);
		Fish &fish = this->allFishes.front();

		// cerr << drone << endl;
		// cerr << fish << endl;

		pair<int, int> vec = {(rand() % 2 ? 1 : -1), (rand() % 2 ? 1 : -1)};

		actions.moveToPos
		(
			fish.x + (vec.first * 1e3),
			fish.y + (vec.second * 1e3),
			drone.battery >= 5
		);
	}

	return ;
}
