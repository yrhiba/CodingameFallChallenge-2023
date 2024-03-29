#include "header.hpp"

/*start*/

int	Game::getClosestVisibleFishNotScannedYet(EVector pos)
{
	int		fishId = -1;
	double	fishDis = -1;

	for (auto &fish : this->allFishes)
	{
		if (fish.type == -1) continue;
		if (fish.visibleAtTurn == -1) continue;
		if (fish.scannedByMe) continue;

		double curDis = calcDistance(fish.pos, pos);

		if ((fishId == -1) || (fishDis > curDis))
		{
			fishId = fish.id;
			fishDis = curDis;
		}
	}

	return (fishId);
}

int		Game::getClosestDroneIdFromPos(EVector pos)
{
	int		droneId = -1;
	double	droneDis = -1;

	for (Drone &drone : this->allDrones)
	{
		if (drone.emergency) continue;

		double curDroneDis = calcDistance(drone.pos, pos);

		if ((droneDis == -1) || (droneDis > curDroneDis))
		{
			droneId = drone.id;
			droneDis = curDroneDis;
		}
	}

	return droneId;
}

Fish &Game::getFishById(int fishId)
{
	int start = 0;
	int end = this->allFishes.size() - 1;
	int mid, ans = -1;

	while (start <= end)
	{
		mid = start + (end - start) / 2;

		if (this->allFishes[mid].id == fishId)
			return this->allFishes[mid];

		if (this->allFishes[mid].id < fishId)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	cerr << "Doe's not find fish with id: " << fishId << endl;
	return this->allFishes.back();
}

Drone &Game::getDroneById(int droneId)
{
	int start = 0;
	int end = this->allDrones.size() - 1;
	int mid, ans = -1;

	while (start <= end)
	{
		mid = start + (end - start) / 2;

		if (this->allDrones[mid].id == droneId)
			return this->allDrones[mid];

		if (this->allDrones[mid].id < droneId)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	cerr << "Doe's not find drone with id: " << droneId << endl;
	return this->allDrones.back();
}

int	Game::getClosestUgly(EVector pos)
{
	int		fishId = -1;
	double	fishDis = -1;

	for (auto &fish : this->allFishes)
	{
		if (fish.type != -1) continue;
		if (fish.visibleAtTurn == -1) continue;

		double curDis = calcDistance(fish.pos, pos);

		if ((fishId == -1) || (fishDis > curDis))
		{
			fishId = fish.id;
			fishDis = curDis;
		}
	}

	return (fishId);
}

vector<int>	Game::getClosestUglysIdFrom(Fish &ugly)
{
	vector<int>	uglyIds;
	double		uglyDis = -1;

	vector<int> &allUglys = this->typeFishes[-1];

	for (int &curUglyId : allUglys)
	{
		if (curUglyId == ugly.id)	continue;

		Fish &curUgly = this->getFishById(curUglyId);

		double range = 600;
		double distance = calcDistance(curUgly.pos, ugly.pos);

		if (distance <= range)
		{
			if (uglyDis == -1)
			{
				uglyIds.push_back(curUgly.id);
				uglyDis = distance;
			}
			else if (distance < uglyDis)
			{
				uglyIds = vector<int>(1, curUgly.id);
				uglyDis = distance;
			}
			else if (distance == uglyDis)
			{
				uglyIds.push_back(curUgly.id);
			}
		}
	}

	return (uglyIds);
}

vector<int>		Game::getDronesTargetForUgly(Fish &ugly)
{
	vector<int>	droneIds;
	int			droneDis = -1;

	for (Drone &drone : this->allDrones)
	{
		if (drone.emergency) continue;

		double range = drone.isLightOn ? 2000 : 800;
		double distance =	(drone.pos.x - ugly.pos.x) * (drone.pos.x - ugly.pos.x) +
							(drone.pos.y - ugly.pos.y) * (drone.pos.y - ugly.pos.y);

		if (distance <= (range * range))
		{
			if (droneDis == -1)
			{
				droneIds.push_back(drone.id);
				droneDis = distance;
			}
			else if (distance < droneDis)
			{
				droneIds = vector<int>(1, drone.id);
				droneDis = distance;
			}
			else if (distance == droneDis)
			{
				droneIds.push_back(drone.id);
			}
		}
	}

	return (droneIds);
}

vector<int>	Game::getClosestDronesForFish(Fish &fish)
{
	vector<int>	droneIds;
	int			droneDis = -1;

	for (Drone &drone : this->allDrones)
	{
		if (drone.emergency) continue;

		double range = 1400;
		double distance =	(drone.pos.x - fish.pos.x) * (drone.pos.x - fish.pos.x) +
							(drone.pos.y - fish.pos.y) * (drone.pos.y - fish.pos.y);

		if (distance <= (range * range))
		{
			if (droneDis == -1)
			{
				droneIds.push_back(drone.id);
				droneDis = distance;
			}
			else if (distance < droneDis)
			{
				droneIds = vector<int>(1, drone.id);
				droneDis = distance;
			}
			else if (distance == droneDis)
			{
				droneIds.push_back(drone.id);
			}
		}
	}
	return (droneIds);
}

vector<int>	Game::getClosestFishesFromFish(Fish &givenFish)
{
	vector<int>	fishIds;
	double		fishDis = -1;

	for (Fish &curfish : this->allFishes)
	{
		if (curfish.id == givenFish.id)	continue;

		double range = 600;
		double distance = calcDistance(curfish.pos, givenFish.pos);

		if (distance <= range)
		{
			if (fishDis == -1)
			{
				fishIds.push_back(curfish.id);
				fishDis = distance;
			}
			else if (distance < fishDis)
			{
				fishIds = vector<int>(1, curfish.id);
				fishDis = distance;
			}
			else if (distance == fishDis)
			{
				fishIds.push_back(curfish.id);
			}
		}
	}
	return (fishIds);
}
