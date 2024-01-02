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

	this->game_turn += 1;
	this->creature_visible_count = 0;

	// initialize + update fishes objects
	for (auto &fish : this->allFishes)
	{
		fish.initializeAndSetupTurnData();
	}

	// TODO:
	// initialize + update fishes objects
	for (auto &drone : this->allDrones)
	{
		// drone.initializeAndSetupTurnData();
	}
}
