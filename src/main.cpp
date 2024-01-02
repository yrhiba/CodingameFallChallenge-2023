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

		/* Read Scores */
		game.readScores();

		/* Read Scanned Creatures (Me, Opponets) */
		game.readScannedCreatures();

		/* Read My Drones and Opponnets Drones */
		if (game.game_turn == 0)
		{
			game.readSetupDrones();
		}
		else
		{
			game.readDrones();
		}

		/* Read Drones current creatures scann */ 
		game.readDronesCurrentScan();

		/* Creatures(fishes) Position */
		game.readVisibleCreatures();

		/* Read Creatures Radar Direction */
		game.readRadarInfo();

		// simulate the uglys
		game.uglysSimulation(); // not code it yet

		// simulate the fishes
		game.fishesSimulation();

		// start of new Turn

		#if DEBUG
		cerr << "Game-Turn: " << game.game_turn << endl << endl;
		#endif

		/* FISHES EVAL MODUL */
		// evaluate target point for remainig fishes //
		game.evaluate_fishes_targets();
		// evaluate fishes possible to kick them out //
		game.fishesEvaluatePossibleToKick();
		// evaluate fishes possible to scan them //
		game.fishesEvaluatePossibleToScan();
		/* FISHES EVAL MODUL */

		// puts the solution
		game.solution();
	}

	return (0);
}
