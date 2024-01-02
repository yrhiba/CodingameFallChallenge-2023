#include "../../header.hpp"

/*start*/

// run once per the hole game
void Game::readSetupCreatures( void )
{
	cin >> this->creature_count;
	this->allFishes.resize(this->creature_count);
	for (auto &fish : this->allFishes)
	{
		fish.initializeAndSetupTurnData();

		cin >> fish; cin.ignore();
		this->typeFishes[fish.type].push_back(fish.id);
	}

	sort(this->allFishes.begin(), this->allFishes.end());
}

void	Game::readSetupDrones(void)
{
	// My Drones Status
	cin >> this->my_drone_count; cin.ignore();

	for (int i = 0; i < this->my_drone_count; i++)
	{
		Drone drone;

		drone.initializeSetupGameData();

		cin >> drone;
		drone.myDrone = 1;
		drone.opDrone = 0;
		this->allDrones.push_back(drone);
		this->myDrones.push_back(drone.id);
	}
	// Oponents Drones Status
	cin >> this->op_drone_count; cin.ignore();

	for (int i = 0; i < this->op_drone_count; i++)
	{
		Drone drone;

		drone.initializeSetupGameData();

		cin >> drone;
		drone.myDrone = 0;
		drone.opDrone = 1;
		this->allDrones.push_back(drone);
		this->opponentsDrones.push_back(drone.id);
	}

	sort(this->allDrones.begin(), this->allDrones.end());
}
