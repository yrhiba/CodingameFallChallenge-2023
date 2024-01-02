#include "../header.hpp"

/*start*/

void	Game::fishesEvaluatePossibleToKick(void)
{
	for (Fish &fish : this->allFishes)
	{
		if (!fish.availableToKick) continue;

		// Add the fish to the list need to kick them before the opponets scan them
		this->fishsPossibleToKick.insert(fish.id);
		this->fishsPossibleToKickType[fish.type].insert(fish.id);
	}
}
