#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	// Debugs Info
	this->debugFishsVisibleSimulated();
	this->debugVisibleSimulatedUglys();
	this->debugFishesPossibleToScan();
	this->debugFishesPossibleToKick();

	// Assign fishes to drones for scan & kick
	this->dronesAssingFishesToScan();
	this->dronesAssingFishesToKickOut();

	for (auto &droneId : this->myDrones)
	{
		Drone	&curDrone = this->getDroneById(droneId);

		if (curDrone.emergency)
		{
			// Do nothing, I don't have control on the drone.
			curDrone.action.setMsg("emergency.");
			// add action with ligh off state
			curDrone.action.wait(false);
		}
		else
		{
			// update velocty
			this->droneUpdateVel(curDrone);
			// avoid uglys
			this->dronesAvoidnes(curDrone);
			// light desion on/off
			this->droneLighEvaluateState(curDrone);
			// update position
			curDrone.updatePos();
			// output the reult action
			curDrone.action.moveToPos(
				curDrone.pos.x,
				curDrone.pos.y,
				curDrone.light
			);
		}
	}

	// debug drones descion
	this->debugDronesActions();
}

/*
To-Work-On:
0 - score the current fishes scan for me and opponents
1 - remove fish from the map

Tips:
0 - don't wast time with the leaderBoard
	the game still not finish yet and play for
	the best bot you code ever, see the details.

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
5 - avoid the uglys with the calculated velocty : done (99.9% work fine) 
6 - algo for lighting the drone or not (depending if i am close enghouf to the target 
	fishes or possible invisble ugly close to me).
7 - update and output the move or the wait : done (100%)

Other-Mission-possible-help:
1 - using radar calc predicted target position for every Fish/Ugly.
2 - calc the score i have currently in my drone and compare it to the opponents one
	if it have the same creatures as mine go to top in the shortest movemment possible
	to gain the bonus.
3 - add if i already scanned the fish and my opponents gonna lose some points
	sifte fish bera map.
*/
