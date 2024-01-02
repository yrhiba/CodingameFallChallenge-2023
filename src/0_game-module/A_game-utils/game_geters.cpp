#include "../header.hpp"

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

