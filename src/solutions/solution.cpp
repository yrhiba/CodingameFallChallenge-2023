#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	cerr << "Game-Turn: " << this->game_turn << endl << endl;

	cerr << "Visible+Simulated-Uglys : " << endl;
	for (int i : this->typeFishes[-1])
	{
		Fish &ugly = this->getFishById(i);
		if (!ugly.isVisible) continue;
		cerr << ugly.id << " " << ugly.pos << " " << ugly.velocty << endl;
	}
	cerr << endl;

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
					EVector(2500, 0),
					EVector(2000, MAP_SIZE - 1000), 
					800
				);
			}
			else
			{
				curDrone.single_line_path = SingleLinePath
				(
					EVector(7500, 0),
					EVector(MAP_SIZE - 2000, MAP_SIZE - 1000),
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

/*
Turn order taches:
0 - simulate the already visible uglys moves (estimation : 99.9% work)
1 - initialize the data from the previous turn (99.9%)
2 - read the data of the current turn (100%)
3 - calc the scores - availlable + possible (if i go to top) (10%)
4 - drones missions. (bellow more detail availble)

Drone: mission order
1 - initialize the velocty and accleration by 0 : done (99.9% work)
2 - remove from the map the fishes already scanned - TO-Do
3 - calc the remaing availlable fishes to scan and there cost : TO-Do
4 - define the target point (path) - calc the velocty : TO-Do
5 - avoid the uglys with the calculated velocty : done (95% work fine)
6 - algo for lighting the drone or not (depending if i am close enghouf to the target fishes or possible invisble ugly close to me).
7 - update and output the move or the wait : done (100%)

Other-Mission-possible-help:
1 - using radar calc predicted target position for every Fish/Ugly.
2 - calc the score i have currently in my drone and compare it to the opponents one
	if it have the same creatures as mine go to top in the shortest movemment possible
	to gain the bonus.
*/
