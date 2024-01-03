#include "header.hpp"

/*start*/

// this function is just for learn and debug purpos it not take part with the final strategie
void	Game::dronesAssingFishesToKickOut(void)
{
	for (int droneId:this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);
		if (drone.assignedFishToKick)
		{
			Fish &fish = this->getFishById(drone.TargetFishToKick);
			fish.availableToKick = false;
			if (fish.scannedByOp || fish.unsavedScanedByOP || fish.dead
				|| fish.deadNextTurn) drone.assignedFishToKick=false,drone.TargetFishToKick=-1;
		}
	}
	set<int>	fishesNeedToKick;
	for (int fishID:this->fishsPossibleToKick)
	{
		Fish &fish = this->getFishById(fishID);
		if (!(fish.availableToKick))continue;
		double range = 2000;
		if (abs(fish.visibleAtTurn - this->game_turn) <= 1
		&& (fish.pos.x <= range || (1e4 - fish.pos.x) <= range))
			fishesNeedToKick.insert(fish.id);
	}
	vector<int> fishesNeedToKickSorted;
	for (int type = 2; type >= 0; type--)
		for (int fishId:this->typeFishes[type])
			if (fishesNeedToKick.count(fishId))
				fishesNeedToKickSorted.push_back(fishId);
	// arguments: fishesNeedToKickSorted | drones-without-kick-assignemt
	// output: best assignment for each fish to a drone with some range
	cerr << "fishes-To-Kick-sorted: " << fishesNeedToKickSorted.size() << endl;
	for (int fishId:fishesNeedToKickSorted)
	{
		cerr << "fish: " << fishId << " ";
		Fish	&fish = this->getFishById(fishId);
		int		droneToAssign = -1;
		double	distance = -1;
		double	range = 5000;
		for (int droneId:this->myDrones)
		{
			Drone &drone = this->getDroneById(droneId);
			if (drone.assignedFishToKick) continue;
			double curDis = calcDistance(drone.pos, fish.pos);
			if ((curDis <= range) && ((distance == -1) || (curDis < distance)))
			{
				droneToAssign = drone.id;
				distance = curDis;
			}
		}
		if (droneToAssign == -1)
		{
			cerr << endl;
			continue;
		}
		cerr << ", Assigned to drone: " << droneToAssign << endl;
		Drone &resDrone = this->getDroneById(droneToAssign);
		resDrone.assignedFishToKick = true;
		resDrone.TargetFishToKick = fish.id;
		fish.availableToKick = false;
	}
}
