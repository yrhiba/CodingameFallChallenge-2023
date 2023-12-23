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

		// Set Velocty to the Drone.
		if (this->game_turn == 0)
		{
			curDrone.velocty = EVector(rand()%2000 - 1000, rand() % 800 + 200);
		}

		// Detect Ugly and Flee from them.
		while (true)
		{
			if (this->uglys_visible_count)
			{
				Fish	&Ugly = this->getClosestUgly(curDrone.pos);
				double	Distance = calcDistance(Ugly.pos, curDrone.pos);

				if (Distance > 900) break;

				actions.setMsg("Ugly Detected::" + to_string(Ugly.id));
			}

			break;
		}

		// Update the drone position in each turn.
		curDrone.updatePos();
		curDrone.edges();
		curDrone.light = (curDrone.battery >= 5 ? (rand()%3 > 0) : 0);
		actions.moveToPos(
			curDrone.pos.x,
			curDrone.pos.y,
			curDrone.light
		);
	}

	return ;
}
