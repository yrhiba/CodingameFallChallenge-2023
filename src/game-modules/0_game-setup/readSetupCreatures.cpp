#include "../../header.hpp"

/*start*/

// run once per the hole game
void Game::readSetupCreatures( void )
{
	cin >> this->creature_count;
	this->allFishes.resize(this->creature_count);
	for (auto &fish : this->allFishes)
	{
		fish.initializeSetupGameData();

		cin >> fish; cin.ignore();
		this->typeFishes[fish.type].push_back(fish.id);
	}

	sort(this->allFishes.begin(), this->allFishes.end());
}
