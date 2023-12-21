#include "../includes/Game.hpp"

/*start*/

Game::Game()
:game_turn(-1)
{
}

void Game::initTurn( void )
{
	this->isScannedFish.clear();
	this->isScannedByMeFish.clear();
	this->isScannedByOpFish.clear();
	this->isDeadFish.clear();

	this->game_turn += 1;
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
			
			rDrone.x = drone.x;
			rDrone.y = drone.y;
			rDrone.emergency = drone.emergency;
			rDrone.battery = drone.battery;
			rDrone.scannedCreatures.clear();
			rDrone.creaturesDirection.clear();
		}

		// Oponents Drones Status
		cin >> this->op_drone_count; cin.ignore();
		for (int i = 0; i < this->op_drone_count; i++)
		{
			Drone drone; cin >> drone;
			
			Drone &rDrone = this->getDroneById(drone.id);
			
			rDrone.x = drone.x;
			rDrone.y = drone.y;
			rDrone.emergency = drone.emergency;
			rDrone.battery = drone.battery;
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
	int visible_creature_count;
	cin >> visible_creature_count; cin.ignore();
	for (int i = 0; i < visible_creature_count; i++)
	{
		int creature_id, creature_x, creature_y, creature_vx, creature_vy;
		cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();

		Fish &fish = this->getFishById(creature_id);

		fish.isVisible = true;
		fish.prev_x = fish.x;
		fish.prev_y = fish.y;
		fish.x = creature_x;
		fish.y = creature_y;
		fish.prev_vx = fish.vx;
		fish.prev_vy = fish.vy;
		fish.vx = creature_vx;
		fish.vy = creature_vy;
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
		mid = start + ((end - start) / 2);

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

	return this->allFishes.back();
}

Drone &Game::getDroneById(int droneId)
{
	int start = 0;
	int end = this->allDrones.size() - 1;
	int mid, ans = -1;

	while (start <= end)
	{
		mid = start + ((end - start) / 2);

		if (this->allDrones[mid].id == droneId)
			return this->allDrones[mid];

		if (this->allFishes[mid].id < droneId)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	return this->allDrones.back();
}

