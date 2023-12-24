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

		if (this->fishes_visible_notScanned_count)
		{
			Fish	&fish = this->getClosestVisibleFishNotScannedYet(curDrone.pos);
			EVector	seekForce = curDrone.seekToPosForce(fish.pos + fish.velocty);
			curDrone.applyForce(seekForce);
		}

		curDrone.updatePos();
		curDrone.edges();

		if (this->game_turn > 4 && curDrone.battery >= 5)
		{
			curDrone.light = (this->game_turn % 2) ? 1 : 0;
		}

		actions.moveToPos(
			curDrone.pos.x,
			curDrone.pos.y,
			curDrone.light
		);
	}

	return ;
}
