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
	game.readCreatures();

	/* Game Loop */
	while (true) 
	{
		cerr << "Game-Turn: " << game.game_turn << endl << endl;

		/* Initialize Data */
		game.initTurn();

		/* Read Scores */
		game.readScores();

		/* Read Scanned Creatures (Me, Opponets) */
		game.readScannedCreatures();

		/* Read My Drones and Opponnets Drones */
		game.readDrones();

		/* Read Drones current creatures scann */ 
		game.readDronesCurrentScan();

		/* Creatures(fishes) Position */
		game.readVisibleCreatures();

		/* Read Creatures Radar Direction */
		game.readRadarInfo();

		// simulate the next position of the visible uglys
		// add a prediction futur pos for all the previous visible Uglys
		game.uglysSimulation();

		// evaluate target point for remainig fishes
		game.evaluate_fishes_targets();

		/* puts the solution */
		game.solution();
	}

	return (0);
}
