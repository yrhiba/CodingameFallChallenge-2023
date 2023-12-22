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

	/*
		PART ZERO:
			- calculate all the visible fishes and uglys for all my drones.
			- calculate the scores (saved and unsaved)
			- mark the danger drones.
			- decide the priorityes PART to be consider first.
	*/

	Actions actions;

	// this->debug();

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);

		/*
			- see if the drone is in danger with the visible uglys positon.

			- mark the visible creatures : done.

			- count the visible fishes | the visible Uglys

			- count the scanned fishes | score and accordine to the global current score gained + current score not saved Yet.

			- see possiblitys of begin the first ho save something

			// PARSING PART : Construct the Information Needed Later.

			// Pre Algo : Use Some Probabilty TO decide predicted best choice (ligh, wait) etc.

			// PART ONE : Calculate the Best MOVE POSITION

			if (countVisible == 0)
			{
				// EXPLORE MORE
			}
			else if (countVisibleUGLY > 0)
			{
				// Flee From them
			}
			else if (countVisibleFishes > 0)
			{
				// DO something with not Saved Yet

				// DO something with already Saved Fishes
			}

			// PART TWO : use some information from the part one to decide if i want to use light or not?

			if (something)
			{
				// light on
			}
			else
			{
				// light off
			}

			FINAL PART: Use all decided action need to be do, and choice the priorityz one!
		*/

		/* add to actions the final descion */
		// actions.moveToPos(curDrone.pos.x, curDrone.pos.y, curDrone.light);
		actions.wait(curDrone.light);
	}

	return ;
}
