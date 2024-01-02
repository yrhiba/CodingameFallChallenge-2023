#include "../header.hpp"

/*start*/

void Game::debugVisibleSimulatedUglys(void)
{
	cerr << "Visible+Simulated-Uglys : ";
	bool	isAtLeastOne = false;
	for (int i : this->typeFishes[-1])
	{
		Fish &ugly = this->getFishById(i);
		if (!ugly.isVisible) continue;
		if (!isAtLeastOne) cerr << endl;
		isAtLeastOne = true;
		cerr << ugly.id << " " << ugly.pos << " " << ugly.velocty << endl;
	}
	if (!isAtLeastOne)
		cerr << " No-Information-Availlable";
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

			if (fish.existZones.size() != 3)
			{
				cerr << "Out-Of-The-Map." << endl;
			}
			else
			{
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

void	Game::debugFishsToKickAssinment(void)
{
	for (int droneID : this->myDrones)
	{
		Drone &drone = this->getDroneById(droneID);

		cerr << "drone: " << drone.id << " ";

		if (drone.assignedFishToKick)
		{
			cerr << "Assigned To Kick Fish: " << drone.TargetFishToKick << endl;
		}
		else
		{
			cerr << "Not Assigned To Kick Any Fish." << endl;
		}
	}
	cerr << endl;
}

void	Game::debugFishesPossibleToKick(void)
{
	cerr << "Fishes-Possible-To-Kick-Ids: " << endl;
	for (int fishId : this->fishsPossibleToKick)
	{
		cerr << fishId << " ";
	}
	cerr << endl << endl;
}

void	Game::debugFishesPossibleToScan(void)
{
	cerr << "Fishes-Possible-To-Scan-Ids: " << endl;
	for (int fishId : this->fishsPossibleToScan)
	{
		cerr << fishId << " ";
	}
	cerr << endl << endl;
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
