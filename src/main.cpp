#include "header.hpp"
#include "Drone.hpp"
#include "Fish.hpp"
#include "Game.hpp"

/*start*/

/* intialize the game */
Game game;

void	GameSetup(void)
{
	/* read Creatures */
	game.readSetupCreatures();
}

void	GameInitTurn(void)
{
	/* Initialize Data */
	game.initTurn();
}

void	GameReadInput(void)
{
	/* read turn data */
	game.readTurnData();
}

void	GameUpdateFishesDrones(void)
{
	/* fishes-updates-turn-data-and-set-flags*/
	game.setFishesFlagsAndUpdates(); // estimated postion + availlavilty to scan + kick //

	/* drones-updates-turn-data-and-set-flags*/
	game.setDronesFlagsAndUpdates(); // check the mission state .. //
}

void	GameSimulation(void)
{
	// simulate the uglys //
	game.uglysSimulation();
	// simulate the fishes //
	game.fishesSimulation();
}

void	GameOutputTurnActions(void)
{
	// start of new Turn //
	// ################ //
	#if DEBUG
	cerr << "Game-Turn: " << game.game_turn << endl << endl;
	#endif

	// puts the solution //
	game.solution();
}

void GameScoringEvaluation(void)
{
	// Evaluate score i have vs opponent
}

int main()
{
	/* Initialize Random Generation */
	srand(time(NULL));

	GameSetup();

	/* Game Loop */
	while (true) 
	{
		GameInitTurn();

		GameReadInput();

		GameUpdateFishesDrones();

		GameSimulation();

		GameScoringEvaluation();

		GameOutputTurnActions();
	}

	return (0);
}
