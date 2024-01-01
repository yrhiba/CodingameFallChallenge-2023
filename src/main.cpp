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

		// start of new Turn
		cerr << "Game-Turn: " << game.game_turn << endl << endl;

		// evaluate the current score Table
		game.scores_evaluate(); // ||| still do nothing for the moment

		// evaluate target point for remainig fishes
		game.evaluate_fishes_targets(); // || calc an estimation postion for the unvisible fishes

		// evaluate fishes possible to kick them out
		game.fishesEvaluatePossibleToKick(); // || map the fishes that my opponents still not scan them yet

		// evaluate fishes possible to scan them
		game.fishesEvaluatePossibleToScan(); // || maybe start with the fishes not scanned by opponts

		/* puts the solution */
		game.solution();
	}

	return (0);
}
