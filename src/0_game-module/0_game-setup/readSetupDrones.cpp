#include "../../header.hpp"

/*start*/

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
