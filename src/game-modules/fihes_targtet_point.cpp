#include "../header.hpp"

/*start*/

pair<EVector, EVector> calcTheIntersctionReactangle(vector<pair<EVector, EVector>> rectangles)
{
	if (rectangles.empty())
	{
		cerr << "No-information-for-that-fish." << endl;
		return {EVector(0, 0), EVector(9999, 9999)};
	}

	double maxLeft = rectangles[0].first.x;
	double maxTop = rectangles[0].first.y;
	double minRight = rectangles[0].second.x;
	double minBottom = rectangles[0].second.y;

	// Iterate through the rectangles to find the intersection
	for (const auto &rect : rectangles)
	{
		maxLeft = max(maxLeft, rect.first.x);
		maxTop = max(maxTop, rect.first.y);
		minRight = min(minRight, rect.second.x);
		minBottom = min(minBottom, rect.second.y);
	}

	// Check if there is a valid intersection
	if (maxLeft < minRight && maxTop < minBottom)
	{
		// Return the intersection rectangle
		return {EVector(maxLeft, maxTop), EVector(minRight, minBottom)};
	}
	else
	{
		cerr << "there-is-something-wrong-with-radar." << endl;
		return {EVector(0, 0), EVector(9999, 9999)};
	}
}

void	Game::evaluate_fishes_targets(void)
{
	cerr << "Fishes To Scan: " << endl;

	for (Fish &fish : this->allFishes)
	{
		// skip the uglys
		if (fish.type == -1) continue;

		// skip the saved fishes
		if (!fish.availlableToscan) continue;

		if (fish.existZones.size() != 3) 
		{
			fish.availlableToscan = false;
			continue;
		}

		fish.existZone = calcTheIntersctionReactangle(fish.existZones);

		EVector vect = fish.existZone.second - fish.existZone.first;

		vect.setMag(calcDistance(fish.existZone.first, fish.existZone.second) / 2.0);

		vect.roundme();

		fish.targetPointToScan = fish.existZone.first + vect;

		cerr << "fish:" << fish.id << " Target: " << fish.targetPointToScan << endl;
	}
}

int		Game::getClosestFishNotScannedYetTarget(Drone &drone)
{
	int		fishId = -1;
	double	fishDis = -1;

	for (auto &fish : this->allFishes)
	{
		if (fish.type == -1) continue;
		if (!fish.availlableToscan) continue;

		double curDis = calcDistance(fish.targetPointToScan, drone.pos);

		if (fish.targetPointToScan.x < 0 || fish.targetPointToScan.x > 9999)
			continue;

		if (fish.targetPointToScan.y < 0 || fish.targetPointToScan.y > 9999)
			continue;

		if ((fishId == -1) || (curDis < fishDis))
		{
			fishId = fish.id;
			fishDis = curDis;
		}
	}

	return (fishId);
}
