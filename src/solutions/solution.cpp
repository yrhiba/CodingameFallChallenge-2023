#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	cerr << "Game-Turn: " << this->game_turn << endl << endl;

	Actions actions;

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);

		if (this->game_turn == 0)
		{
			if (curDrone.pos.x < 5e3)
			{
				curDrone.single_line_path = SingleLinePath
				(
					EVector(5e3, 0),
					EVector(0, MAP_SIZE), 
					800
				);
			}
			else
			{
				curDrone.single_line_path = SingleLinePath
				(
					EVector(5e3, 0),
					EVector(MAP_SIZE, MAP_SIZE),
					800
				);
			}
		}

		curDrone.velocty = curDrone.followSingleLinePathForce();

		if (curDrone.single_line_path.isFinish())
		{
			curDrone.single_line_path.reset();
			curDrone.single_line_path.reverseDirection();

			curDrone.velocty = curDrone.followSingleLinePathForce();
		}

		this->dronesAvoidnes(curDrone);

		curDrone.updatePos();

		if (this->game_turn > 4 && curDrone.battery >= 5 && curDrone.pos.y > 3000)
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
