#include "Game.hpp"

/*start*/

void	Game::setDronesFlagsAndUpdates(void)
{
	Drone &drone1=this->getDroneById(this->myDrones.front());
	Drone &drone2=this->getDroneById(this->myDrones.back());
	drone1.leftDrone=(drone1.pos.x<=drone2.pos.x);
	drone2.rightDrone=drone1.leftDrone;
	drone1.rightDrone=!drone1.leftDrone;
	drone2.leftDrone=!drone2.rightDrone;
	//#################################
	for (int droneId:this->myDrones)
	{
		Drone &drone=this->getDroneById(droneId);
		if (drone.assignedFishToScan)
		{
			Fish &fish = this->getFishById(drone.TargetFishToScan);
			if (fish.availlableToscan) continue;
			drone.assignedFishToScan = false;
			drone.TargetFishToScan = -1;
		}
		if (drone.assignedFishToKick)
		{
			Fish &fish = this->getFishById(drone.TargetFishToKick);
			if (fish.availableToKick) continue;
			drone.assignedFishToKick = false;
			drone.TargetFishToKick = -1;
		}
	}
}
