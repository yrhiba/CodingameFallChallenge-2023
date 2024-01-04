#include "header.hpp"

/*start*/

void		Game::fishesSimulation(void)
{
	for (Fish &fish : this->allFishes)
	{
		if ((fish.type == -1) || fish.dead) continue;
		if ((fish.visibleAtTurn == this->game_turn) || (fish.visibleAtTurn == -1)) continue;
		fish.pos += fish.velocty;
		fish.snapToZone();
	}
	for (Fish &fish : this->allFishes)
	{
		if ((fish.type == -1) || fish.dead) continue;
		if ((fish.visibleAtTurn == this->game_turn) || (fish.visibleAtTurn == -1)) continue;
		vector<int> closestDrones = getClosestDronesForFish(fish);
		if (!closestDrones.empty())
		{
			// will flee
			EVector fleePos = EVector(0, 0);
			for (int &droneId : closestDrones)
				fleePos += this->getDroneById(droneId).pos;
			fleePos /= closestDrones.size();
			fish.velocty = fish.pos - fleePos;
			fish.velocty.setMag(400);
			fish.velocty.roundme();
		}
		else
		{
			// will not flee
			fish.velocty.setMag(200);
			fish.velocty.roundme();
			vector<int> closesFishes = this->getClosestFishesFromFish(fish);
			if (!closesFishes.empty())
			{
				EVector targetPos = EVector(0, 0);
				for (int &fishID : closesFishes)
					targetPos += this->getFishById(fishID).pos;
				targetPos /= closesFishes.size();
				fish.velocty = fish.pos - targetPos;
				fish.velocty.setMag(200);
				fish.velocty.roundme();
			}
			double	minY = fish.existZones.front().first.y;
			double	maxY = fish.existZones.front().second.y;
			EVector	nextPos = fish.pos + fish.velocty;
			if ((nextPos.x < 0 && nextPos.x < fish.pos.x) ||
				(nextPos.x > 9999 && nextPos.x > fish.pos.x))
			{
				fish.velocty.x *= -1;
			}
			if ((nextPos.y < minY && nextPos.y < fish.pos.y) || 
				(nextPos.y > maxY && nextPos.y > fish.pos.y))
			{
				fish.velocty.y *= -1;
			}
		}
		// flag if the next turn the fish gonna die
		fish.deadNextTurn = fish.isDeadNextTurn();
	}
}
