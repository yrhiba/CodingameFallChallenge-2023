#include "../includes/Game.hpp"

/*start*/

Game::Game()
:game_turn(-1)
{
}

void Game::readCreatures( void )
{
	cin >> this->creature_count;
	this->allFishes.resize(this->creature_count);
	for (auto &fish : this->allFishes)
	{
		cin >> fish; cin.ignore();
		this->typeFishes[fish.type].push_back(fish.id);
	}
	sort(this->allFishes.begin(), this->allFishes.end());
}

void Game::initTurn( void )
{
	this->isScannedFish.clear();
	this->isScannedByMeFish.clear();
	this->isScannedByOpFish.clear();
	this->isDeadFish.clear();

	this->creature_visible_count = 0;
	this->fishes_visible_count = 0;
	this->fishes_visible_notScanned_count = 0;
	this->uglys_visible_count = 0;

	for (auto &fish : this->allFishes)
	{
		if (fish.type != -1)
		{
			fish.isVisible = false;
			fish.pos = EVector(-1, -1);
		}
	}

	this->game_turn += 1;
}

void Game::readScores( void )
{
	cin >> this->my_score >> this->op_score;
	cin.ignore();
}

void Game::readScannedCreatures( void )
{
	/* What Me I Scan */
	cin >> this->my_scan_count; cin.ignore();
	for (int i = 0; i < this->my_scan_count; i++)
	{
		int creature_id;
		cin >> creature_id; cin.ignore();

		Fish &fish = this->getFishById(creature_id);

		this->isScannedByMeFish[fish.id] = true;
		this->isScannedFish[fish.id] = true;
		fish.scannedByMe = true;
		fish.scaned = true;
	}

	/* What Oponnents Scan */
	cin >> this->op_scan_count; cin.ignore();
	for (int i = 0; i < this->op_scan_count; i++)
	{
		int creature_id;
		cin >> creature_id; cin.ignore();

		Fish &fish = this->getFishById(creature_id);
		fish.scaned = true;
		fish.scannedByOp = true;
		this->isScannedByOpFish[creature_id] = true;
		this->isScannedFish[creature_id] = true;
	}
}

void Game::readDrones( void )
{
	if (this->game_turn)
	{
		// My Drones Status
		cin >> this->my_drone_count; cin.ignore();
		for (int i = 0; i < this->my_drone_count; i++)
		{
			Drone drone; cin >> drone;

			Drone &rDrone = this->getDroneById(drone.id);

			rDrone.isLightOn = (rDrone.battery - 5 == drone.battery);

			rDrone.pos = drone.pos;
			rDrone.emergency = drone.emergency;
			rDrone.battery = drone.battery;
			rDrone.light = 0;
			rDrone.scannedCreatures.clear();
			rDrone.creaturesDirection.clear();
		}

		// Oponents Drones Status
		cin >> this->op_drone_count; cin.ignore();
		for (int i = 0; i < this->op_drone_count; i++)
		{
			Drone drone; cin >> drone;
			
			Drone &rDrone = this->getDroneById(drone.id);

			rDrone.isLightOn = (rDrone.battery - 5 == drone.battery);

			rDrone.pos = drone.pos;
			rDrone.emergency = drone.emergency;
			rDrone.battery = drone.battery;
			rDrone.light = 0;
			rDrone.scannedCreatures.clear();
			rDrone.creaturesDirection.clear();
		}
	}
	else
	{
		// My Drones Status
		cin >> this->my_drone_count; cin.ignore();
		for (int i = 0; i < this->my_drone_count; i++)
		{
			Drone drone; cin >> drone;
			drone.myDrone = 1;
			drone.opDrone = 0;
			this->allDrones.push_back(drone);
			this->myDrones.push_back(drone.id);
		}
		// Oponents Drones Status
		cin >> this->op_drone_count; cin.ignore();
		for (int i = 0; i < this->op_drone_count; i++)
		{
			Drone drone; cin >> drone;
			drone.myDrone = 0;
			drone.opDrone = 1;
			this->allDrones.push_back(drone);
			this->opponentsDrones.push_back(drone.id);
		}

		sort(this->allDrones.begin(), this->allDrones.end());
	}
}

void Game::readDronesCurrentScan( void )
{
	int drone_scan_count;
	cin >> drone_scan_count; cin.ignore();
	for (int i = 0; i < drone_scan_count; i++)
	{
		int drone_id;
		int creature_id;
		cin >> drone_id >> creature_id; cin.ignore();

		Drone &drone = this->getDroneById(drone_id);
		drone.scannedCreatures.push_back(creature_id);
	}
}

void Game::readVisibleCreatures( void )
{
	/* Creatures (fishes) positions */
	cin >> this->creature_visible_count; cin.ignore();
	for (int i = 0; i < this->creature_visible_count; i++)
	{
		int creature_id, creature_x, creature_y, creature_vx, creature_vy;
		cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();

		Fish &fish = this->getFishById(creature_id);

		this->fishes_visible_count += (fish.type >= 0);
		this->fishes_visible_notScanned_count += (fish.type >= 0 && !fish.scannedByMe);
		this->uglys_visible_count += (fish.type == -1);

		if ((fish.type == -1) && fish.isVisible) continue;

		fish.isVisible = true;
		fish.pos = EVector(creature_x, creature_y);
		fish.velocty = EVector(creature_vx, creature_vy);
	}
}

void Game::readRadarInfo( void )
{
	int radar_blip_count; cin >> radar_blip_count; cin.ignore();
	for (int i = 0; i < radar_blip_count; i++)
	{
		int drone_id, creature_id; string radar;
		cin >> drone_id >> creature_id >> radar; cin.ignore();

		Drone &drone = this->getDroneById(drone_id);
		drone.creaturesDirection.push_back({creature_id, radar});
	}
}

void Game::debug( void )
{
	cerr << "Turn: " << this->game_turn << endl;
	cerr << "Creaturs-Count: " << this->creature_count << endl;
	cerr << "MyScore: " << this->my_score << " | OpScore: " << this->op_score << endl;
	cerr << "MyDroneCount: " << this->my_drone_count << " | OpDroneCount: " << this->op_drone_count << endl;
	cerr << "MyScanCount: " << this->my_scan_count << " | OpScanCount: " << this->op_scan_count << endl;  
	cerr << endl;

	cerr << "Fishes Informations: " << endl;
	for (auto &fish : this->allFishes)
		cerr << fish << endl;
	cerr << endl;

	cerr << "Drones Informations: " << endl;
	for (auto &drone : this->allDrones)
	{
		cerr << drone << endl;
		cerr << "Drone Creatures Radar: " << endl;
		for (auto &[creatureID, direction] : drone.creaturesDirection)
			cerr << creatureID << "," << direction << " | ";
		cerr << endl << endl;
	}
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


/*new-funciton-in-testing-mode-start*/

// get the closest ugly fish from the given position
int	Game::getClosestUgly(EVector pos)
{
	int		fishId = -1;
	double	fishDis = -1;

	for (auto &fish : this->allFishes)
	{
		if (fish.type != -1) continue;
		if (!fish.isVisible) continue;

		double curDis = calcDistance(fish.pos, pos);

		if ((fishId == -1) || (fishDis > curDis))
		{
			fishId = fish.id;
			fishDis = curDis;
		}
	}

	return (fishId);
}

/*
to update it need to take a drone as argument and ignore the fishes
that are already scanned by it, i guess this function need to be implemented inside
drone.cpp file | but anyway i am gonna work on that today no time to waste.
*/
// get the closest visible fish or simulated fish to the given position
int	Game::getClosestVisibleFishNotScannedYet(EVector pos)
{
	int		fishId = -1;
	double	fishDis = -1;

	for (auto &fish : this->allFishes)
	{
		if (fish.type == -1) continue;
		if (!fish.isVisible) continue;
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

// get closest drone from the given position
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

void	Game::uglysSimulation(void)
{
	// cerr << "Ugly TO simulate" << endl;

	// TODO: TODAY
	vector<int> &allUglys = this->typeFishes[-1];

	if (allUglys.empty())
	{
		// there is no visible or uglys at the game.
		return ;
	}

	for (int UglyId : allUglys)
	{
		Fish &ugly = this->getFishById(UglyId);

		if (!ugly.isVisible) continue;

		// TODO return the closest Drone within it's Light Radius
		// int droneID = this->updateTarget(ugly);

		// if (droneID != -1)
		// {
		// 	ugly.pos += ugly.velocty;

		// 	if (ugly.pos.x < 0)
		// 		ugly.pos.x = 0;
		// 	else if (ugly.pos.x > 9999)
		// 		ugly.pos.x = 9999;

		// 	if (ugly.pos.y < 2500)
		// 		ugly.pos.y = 0;
		// 	else if (ugly.pos.y > 9999)
		// 		ugly.pos.y = 9999;

		// 	ugly.pos 
		// }
		// else
		// {

		// }

		// cerr << ugly << endl;
	}
}

/*new-funciton-in-testing-mode-end*/