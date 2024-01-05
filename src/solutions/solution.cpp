#include "header.hpp"
#include "Drone.hpp"
#include "Fish.hpp"
#include "Game.hpp"
#include "Actions.hpp"

/*start*/

void Game::solution()
{
	cerr << "Game-Turn: " << this->game_turn << endl;

	#if DEBUG
	this->debugFishsVisibleSimulated();
	this->debugVisibleSimulatedUglys();
	this->debugFishesPossibleToScan();
	this->debugFishesPossibleToKick();
	#endif

	// Assign fishes to drones for scan & kick
	// this->dronesAssingFishesToKickOut();
	// this->dronesExploreFishesAndTheMap();

	for (auto &droneId : this->myDrones)
	{
		Drone	&curDrone = this->getDroneById(droneId);

		if (curDrone.emergency)
		{
			// Do nothing, I don't have control on the drone.
			curDrone.action.setMsg("Emergency-Mode.");
			// add action with ligh off state
			curDrone.action.wait(false);
		}
		else
		{
			// update mission and velocty
			this->droneUpdateVel(curDrone);
			// update the velocty if uglys/edges coillision detected
			this->dronesAvoidnes(curDrone);
			// light desion on/off based on target fishes to scan and invisible uglys estimation distance + battery state.
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

	#if DEBUG
	this->debugDronesActions();
	#endif
}

