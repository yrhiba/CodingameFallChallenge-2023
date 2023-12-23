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


		Fish &fish = this->getClosestVisibleFishNotScannedYet(curDrone.pos);

		// actions.setMsg(to_string(fish.id));
		curDrone.seekToPos(EVector(5e3, 5e3));

		cerr << curDrone.pos << " " << curDrone.pos.magnitude() << endl;
		cerr << curDrone.velocty << " " << curDrone.velocty.magnitude() << endl;
		cerr << curDrone.acceleration << " " << curDrone.acceleration.magnitude() << endl;

		// Update the drone position in each turn.
		curDrone.updatePos();
		// curDrone.edges();
		curDrone.light = (curDrone.battery >= 5 ? (rand()%3 > 0) : 0);
		actions.moveToPos(
			curDrone.pos.x,
			curDrone.pos.y,
			curDrone.light
		);
	}

	return ;
}
