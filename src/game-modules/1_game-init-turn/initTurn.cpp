#include "header.hpp"

/*start*/

void Game::clearGamePreviousTurnData(void)
{
	this->fishsPossibleToScan.clear();
	this->fishsPossibleToKick.clear();
	for (int type = 0; type <= 2; type++)
	{
		this->fishsPossibleToScanType[type].clear();
		this->fishsPossibleToKickType[type].clear();
	}
}

void	Game::initializeAndUpdateTurnData(void)
{
	// initialize Game object variable
	this->clearGamePreviousTurnData();

	// increment the count of the turn indicator
	this->game_turn += 1;

	// initialize + update fishes objects
	for (auto &fish : this->allFishes)
	{
		fish.initializeAndSetupTurnData();
	}

	// initialize + update drones objects
	for (auto &drone : this->allDrones)
	{
		drone.initializeAndSetupTurnData();
	}
}

void Game::initTurn( void )
{
	// initialize + update variballs of Game/Fishes/Uglys
	this->initializeAndUpdateTurnData();
}
