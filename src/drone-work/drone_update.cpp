#include "../header.hpp"

/*start*/

void Game::droneUpdateVel(Drone &drone)
{
	// must go to kick a fish out of the map
	if (drone.assignedFishToKick)
	{
		drone.action.setMsg("Kick-Fish-" + to_string(drone.TargetFishToKick));
		this->droneUpdateVelToKickOutTheTargetFish(drone);
	}
	// must go to scan a fish
	else if (drone.assignedFishToScan)
	{
		drone.action.setMsg("Scan-Fish-" + to_string(drone.TargetFishToScan));
	}
	// must go to top | save the scanned fishes
	else
	{
		if (drone.pos.y > 500)
		{
			// move to Top
			drone.action.setMsg("Going-To-Top");
			drone.velocty = EVector(0, -600);
		}
		else
		{
			// Do Nothing
			drone.action.setMsg("No-Work-To-Do");
			drone.velocty = EVector(0, 0);
		}
	}
}

/*

Simple Staragtegie To Try version 0.1:

####### Mode 1:
- scan type 2 fishes -> save them
- scan type 1 fishes -> save them
- scan type 0 fishes -> save them

###### Mode 2:
FOR eachVisibleFish
|||||||||||||||||||
if (Fish scanned By Me and not Scanned By Opponent)
{
	if (cost to kick it Out Of the map < maxCostPossibleToKickOutAFish)
	{
		KickTheFish();
	}
	else
	{
		// keep the drone mission.
	}
}
End FOR
||||||||||||||||||||


###### Mode 3:
if (MODE_1_RESULT == NULL && MODE_2_RESULT == NULL)
{
	Look for reaming fishes not scanned yet by the opponnets
	and kick the out of the map.
}
else
{
	The game must be finished.
	congratulation My Self | whatever the result is
	i did my best and jiji for the winner and
	hope you enjoying the game peace and love
	for evrey one work with respect and the hope
	i am verry happy with what i achieve
	and the why how i work.
}


////// strategie version 0.1 completed need to be done asap
anyway ideas to try and updates in the next version:

-	add scoring table and see what currentl score i have
	and what opponets have and see if there is some
	possibilty that he can save the same fishes before me
	and go to top if that true;

-	if we have common fishes scanned with close score
	go to top in the closest time possible.

-	add more logic and best usage of the light.
	(use the light only if i am in a radius of some target fish or ugly area).

Summary: in the last days of the challenge need to play
for scores, till there the movement and best strategies
to explore and scanned the fishes on the map must be try and evaluated.

*/
