#include "../includes/Game.hpp"

/*start*/

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
		int creature_id; cin >> creature_id; cin.ignore();
		Fish &fish = this->getFishById(creature_id);
		fish.scannedByMe = true;
		fish.scaned = true;
	}
	/* What Oponnents Scan */
	cin >> this->op_scan_count; cin.ignore();
	for (int i = 0; i < this->op_scan_count; i++)
	{
		int creature_id; cin >> creature_id; cin.ignore();
		Fish &fish = this->getFishById(creature_id);
		fish.scaned = true;
		fish.scannedByOp = true;
	}
}

void Game::readDrones( void )
{
	cin >> this->my_drone_count; cin.ignore();

	for (int i = 0; i < this->my_drone_count; i++)
	{
		Drone drone; cin >> drone;

		Drone &rDrone = this->getDroneById(drone.id);

		rDrone.isLightOn = (rDrone.battery - 5 == drone.battery);
		rDrone.pos = drone.pos;
		rDrone.emergency = drone.emergency;
		rDrone.battery = drone.battery;
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
	}
}

void Game::readDronesCurrentScan( void )
{
	int drone_scan_count; cin >> drone_scan_count; cin.ignore();

	for (int i = 0; i < drone_scan_count; i++)
	{
		int drone_id, creature_id; cin >> drone_id >> creature_id; cin.ignore();

		Drone	&drone = this->getDroneById(drone_id);
		Fish	&fish = this->getFishById(creature_id);

		drone.scannedCreatures.push_back(fish.id);

		fish.dronesScan.insert(drone.id);

		if (drone.opDrone) // opponets drone
		{
			fish.unsavedScanedByOP = true;
			fish.opDronesScan.insert(drone.id);
		}
		else // my Drone
		{
			fish.unsavedScanedByMe = true;
			fish.myDronesScan.insert(drone.id);
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

		fish.visibleAtTurn = this->game_turn;
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

		Drone	&drone = this->getDroneById(drone_id);
		Fish	&fish = this->getFishById(creature_id);

		fish.pushExistZone(drone.pos, radar);
	}

	for (Fish &fish : this->allFishes)
	{
		if (fish.existZones.size() != 3)
		{
			fish.dead = true;
		}
	}
}

void Game::readTurnData(void)
{
	/* Read Scores */
	this->readScores();

	/* Read Scanned Creatures (Me, Opponets) */
	this->readScannedCreatures();

	/* Read My Drones and Opponnets Drones */
	if (this->game_turn == 0)
	{
		this->readSetupDrones();
	}
	else
	{
		this->readDrones();
	}

	/* Read Drones current creatures scann */ 
	this->readDronesCurrentScan();

	/* Creatures(fishes) Position */
	this->readVisibleCreatures();

	/* Read Creatures Radar Direction */
	this->readRadarInfo();
}

void Game::setFishesFlagsAndUpdates(void)
{
	for (Fish &fish : this->allFishes)
	{
		if (fish.type == -1) continue;

		if (fish.dead) continue;

		fish.setAvaillabilty();
		fish.extimatePossiblePosition();

		if (fish.availlableToscan)
		{
			this->fishsPossibleToScan.insert(fish.id);
			this->fishsPossibleToScanType[fish.type].insert(fish.id);
		}

		if (fish.availableToKick)
		{
			this->fishsPossibleToKick.insert(fish.id);
			this->fishsPossibleToKickType[fish.type].insert(fish.id);
		}
	}
}

void	Game::setDronesFlagsAndUpdates(void)
{
	for (Drone &drone : this->allDrones)
	{
		if (drone.opDrone) continue;

		// TODO: Evaluate mision|queue_mission
	}
}
