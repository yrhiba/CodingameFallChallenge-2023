#include "../header.hpp"

/*start*/

void Game::debugVisibleSimulatedUglys(void)
{
	cerr << "Visible+Simulated-Uglys : " << endl;
	bool	isAtLeastOne = false;
	for (int i : this->typeFishes[-1])
	{
		Fish &ugly = this->getFishById(i);
		if (!ugly.isVisible) continue;
		isAtLeastOne = true;
		cerr << ugly.id << " " << ugly.pos << " " << ugly.velocty << endl;
	}
	if (!isAtLeastOne)
		cerr << "No-Information-Availlable";
	cerr << endl << endl;
}

void Game::debugFishsVisibleSimulated(void)
{
	cerr << "Visible+Simulated-Fishes : " << endl;

	for (int fishType = 2; fishType >= 0; fishType--)
	{
		cerr << "######### Fishes-Type: " << fishType << endl;

		for (int fishId : this->typeFishes[fishType])
		{
			Fish &fish = this->getFishById(fishId);

			cerr << "Fish: " << fish.id << " ";

			if (fish.isVisible)
			{
				cerr << "Pos" << fish.pos << ", Vel" << fish.velocty;
			}
			else
			{
				cerr << "Estimated-Pos: " << fish.targetPointToScan;
			}

			cerr << ", AvaillableToScan: " << (fish.availlableToscan?"yes":"no") << endl;
		}
	}

	cerr << endl;
}

void Game::debugMyDroneState(void)
{
	cerr << "Drones-next-Turn-Estimation-Result:" << endl;
	for (int &droneId : this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);
		cerr << "drone: " << drone.id << " Pos" << drone.pos << " Vel" << drone.velocty;
		cerr << " Light:" << (drone.light? "on" : "off") << endl;
	}
	cerr << endl;
}

// output the sved fishes + the current score | me and opponets
void Game::debugSavedScore(void)
{
}

// output the currently fishes scanned by the drones but not saved Yet
void Game::debugUnsavedScore(void)
{
}

// output Resume of the score
void Game::debugScoring(void)
{
}
