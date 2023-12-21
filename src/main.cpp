#include "include.hpp"
#include "classes/Drone.cpp"
#include "classes/Fish.cpp"
#include "classes/Game.cpp"

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

		/* puts the solution */
		game.solution();
	}
}