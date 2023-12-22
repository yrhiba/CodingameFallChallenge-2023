#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	// cerr << "Visible Creatures: " << this->creature_visible_count << endl;
	// cerr << "Visible Fishes: " << this->fishes_visible_count << endl;
	// cerr << "Visible Uglys: " << this->uglys_visible_count << endl;

	Actions actions;

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);


		cerr << curDrone << endl;
		cerr << "Pos: " << curDrone.pos << " " << curDrone.pos.magnitude() << endl;
		cerr << "Vel: " << curDrone.velocty << " " << curDrone.velocty.magnitude() << endl;
		cerr << "Acc: " << curDrone.acceleration << " " << curDrone.acceleration.magnitude() << endl;

		// EXPLORE MODE
		if (curDrone.pos.x < 200 || curDrone.pos.x > 9800)
		{
			curDrone.velocty.x *= -1;
		}

		if (curDrone.pos.y < 200 || curDrone.pos.y > 9800)
		{
			curDrone.velocty.y *= -1;
		}

		curDrone.velocty += curDrone.acceleration;
		curDrone.pos += curDrone.velocty;

		actions.moveToPos(curDrone.pos.x, curDrone.pos.y, curDrone.light);

		cerr << endl;
	}

	return ;
}
