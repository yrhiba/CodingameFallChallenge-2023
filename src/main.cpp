#include "header.hpp"
#include "includes/Drone.hpp"
#include "includes/Fish.hpp"
#include "includes/Game.hpp"

/*start*/

int main()
{
	/* Initialize Random Generation */
	srand(time(NULL));

	/* intialize the game */
	Game game;

	/* read Creatures */
	game.readSetupCreatures();

	/* Game Loop */
	while (true) 
	{
		/* Initialize Data */
		game.initTurn();

		/*read turn data*/
		game.readTurnData();

		/*fishes-updates-turn-data-and-set-flags*/
		game.setFishesFlagsAndUpdates(); // estimated postion + availlavilty to scan + kick //

		// simulate the uglys
		game.uglysSimulation(); // not code it yet

		// simulate the fishes
		game.fishesSimulation();

		// start of new Turn

		#if DEBUG
		cerr << "Game-Turn: " << game.game_turn << endl << endl;
		#endif

		// puts the solution
		game.solution();
	}

	return (0);
}
