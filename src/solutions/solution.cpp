#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	cerr << "Visible Creatures: " << this->creature_visible_count << endl;
	cerr << "Visible Fishes: " << this->fishes_visible_count << endl;
	cerr << "Visible Uglys: " << this->uglys_visible_count << endl;

	Actions actions;

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);

		cerr << curDrone << endl;

		cerr << "Pos: " << curDrone.pos << endl;
		cerr << "Vel: " << curDrone.velocty << endl;
		cerr << "Acc: " << curDrone.acceleration << endl;

		if (this->creature_visible_count == 0)
		{
			// EXPLORE MODE
			curDrone.velocty += curDrone.acceleration;
			curDrone.pos += curDrone.velocty;

			actions.moveToPos(curDrone.pos.x, curDrone.pos.y, curDrone.light);
		}
		else
		{
			cout << "WAIT 0 Visible-Creatures" << endl;
		}
	}

	return ;
}
