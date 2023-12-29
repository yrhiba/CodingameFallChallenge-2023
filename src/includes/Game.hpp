#pragma once
#include "../header.hpp"
#include "../includes/Drone.hpp";
#include "../includes/Fish.hpp"

/*start*/

struct Game
{
	// Total creatures in the Map
	int	game_turn;

	int	creature_count;
	int	creature_visible_count;
	int	fishes_visible_notScanned_count;
	int	fishes_visible_count;
	int	uglys_visible_count;

	int	my_score;
	int	my_scan_count;
	int	my_drone_count;

	int	op_score;
	int	op_scan_count;
	int	op_drone_count;

	// Fishes Informations
	vector<Fish>				allFishes;
	map<int, vector<int>>		typeFishes;
	map<int, bool>				isScannedFish;
	map<int, bool>				isScannedByMeFish;
	map<int, bool>				isScannedByOpFish;
	map<int, bool>				isDeadFish;

	// Drone Informations
	vector<Drone>				allDrones;
	vector<int>					myDrones;
	vector<int>					opponentsDrones;

	Game();

	void initTurn( void );

	// member function utilitys
	void readCreatures( void );
	void readScores( void );
	void readScannedCreatures( void );
	void readDrones( void );
	void readDronesCurrentScan( void );
	void readVisibleCreatures( void );
	void readRadarInfo( void );

	Fish &getFishById(int fishId);
	Drone &getDroneById(int droneId);

	int		getClosestUgly(EVector pos); // -1 if not found
	int		getClosestVisibleFishNotScannedYet(EVector pos); // -1 if there is no visible fish
	int		getClosestDroneIdFromPos(EVector pos); // -1 if not found

	/*ugly-simulation*/
	void		updateUglySpeed(Fish &ugly);
	void		snapUglyToZone(EVector &uglyPos);
	void		uglysSimulation(void);
	vector<int>	getClosestUglysIdFrom(Fish &ugly);
	vector<int>	uglysDroneIdTarget(Fish &ugly);
	/*ugly-simulation*/


	/*drone-avoidness*/
	bool	getCollision(Drone &drone, Fish &ugly);
	bool	goodDroneVelocty(Drone &drone);
	void	dronesAvoidnes(Drone &drone);
	bool	isCoillisionBetwDroneUgly(Drone &drone, Fish &ugly);
	/*drone-avoidness*/

	void	debug();
	void	solution();
};

