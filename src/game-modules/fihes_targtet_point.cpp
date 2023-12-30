#include "../header.hpp"

/*start*/

void	Game::evaluate_fishes_targets(void)
{
	cerr << "Fishes To Scan: " << endl;

	for (Fish &fish : this->allFishes)
	{
		// skip the uglys
		if (fish.type == -1) continue;

		// skip the saved fishes
		if (!fish.availlableToscan) continue;

		cerr << fish << endl;
	}
}


/*
fish-type-1 => start(0, 2500) -> end(9999, 5000) -> Zone
fish-type-2 => start(0, 5000) -> end(9999, 7500) -> Zone
fish-type-2 => start(0, 7500) -> end(9999, 9999) -> Zone
*/

/*
	TODO: Calculate the zone where the fish is.

	Information i have:
	------------------------------------
	(fish.zone.start) -> (fish.zone.end)
		+
	for (drone : mydrones)
	{
		if (TL)
		{
			(0, 0) -> (drone.pos.x, drone.pos.y)
		}

		if (BR)
		{
			(drone.pos.x, drone.pos.y) -> (9999, 9999)
		}

		if (TR)
		{
			(drone.pos.x, drone.pos.y) -> (0, 9999)
		}

		if (BL)
		{
			(9999, 0) -> (drone.pos.x, drone.pos.y)
		}
	}
	-----------------------------------------------
*/
