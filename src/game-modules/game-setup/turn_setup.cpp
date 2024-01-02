#include "../../header.hpp"

/*start*/

void Game::clearGamePreviousTurnData(void)
{
	this->isScannedFish.clear();
	this->isScannedByMeFish.clear();
	this->isScannedByOpFish.clear();
	this->isDronesScannedByMeFish.clear();
	this->isDronesScannedByOpFish.clear();
	this->isDeadFish.clear();

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
	this->game_turn += 1;
	this->creature_visible_count = 0;
}

void	Game::initializeAndUpdateFishesTurnData(void)
{
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
}
