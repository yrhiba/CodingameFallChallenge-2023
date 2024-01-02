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
	this->isDronesScannedByMeFish.clear();
	this->isDronesScannedByOpFish.clear();
	this->isDeadFish.clear();
	this->fishsPossibleToKick.clear();
	this->fishsPossibleToScan.clear();

	for (int type = 0; type <= 2; type++)
	{
		this->fishsPossibleToKickType[type].clear();
		this->fishsPossibleToScanType[type].clear();
	}

	this->creature_visible_count = 0;
	this->fishes_visible_count = 0;
	this->fishes_visible_notScanned_count = 0;
	this->uglys_visible_count = 0;

	for (auto &fish : this->allFishes)
	{
		if (fish.type == -1) continue;

		fish.availableToKick = true;
		fish.availlableToscan = true;
		fish.existZone = make_pair(EVector(-1, -1), EVector(-1, -1));
		fish.targetPointToScan = EVector(-1, -1);
		fish.existZones.clear();

		// push back the fish zone depending on their type
		if (fish.type == 0)
		{
			fish.existZones.push_back({EVector(0, 2500), EVector(9999, 5000)});
		}
		else if (fish.type == 1)
		{
			fish.existZones.push_back({EVector(0, 5000), EVector(9999, 7500)});
		}
		else if (fish.type == 2)
		{
			fish.existZones.push_back({EVector(0, 7500), EVector(9999, 9999)});
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
		fish.availlableToscan = false;
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
			rDrone.action = Actions();
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
			drone.action = Actions();
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
		int drone_id, creature_id;

		cin >> drone_id >> creature_id; cin.ignore();

		Drone &drone = this->getDroneById(drone_id);

		drone.scannedCreatures.push_back(creature_id);

		if (drone.opDrone)
		{
			this->isDronesScannedByOpFish[creature_id].insert(drone.id);
		}
		else if (drone.myDrone)
		{
			Fish &fish = this->getFishById(creature_id);
			fish.availlableToscan = false;
			this->isDronesScannedByMeFish[creature_id].insert(drone.id);
		}
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

		fish.visibleAtTurn = -1;
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

		Fish &fish = this->getFishById(creature_id);

		// push back the fish zone depending on direction given by radar
		if (radar == "TL")
		{
			fish.existZones.push_back({EVector(0, 0), drone.pos});
		}
		else if (radar == "TR")
		{
			fish.existZones.push_back({EVector(drone.pos.x, 0), EVector(9999, drone.pos.y)});
		}
		else if (radar == "BR")
		{
			fish.existZones.push_back({drone.pos, EVector(9999, 9999)});
		}
		else if (radar == "BL")
		{
			fish.existZones.push_back({EVector(0, drone.pos.y), EVector(drone.pos.x, 9999)});
		}
	}
}

