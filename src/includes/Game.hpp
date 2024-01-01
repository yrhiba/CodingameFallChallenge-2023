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
	set<int>					fishsPossibleToKick;

	map<int, bool>				isScannedByMeFish;
	map<int, bool>				isScannedByOpFish;
	map<int, set<int> >			isDronesScannedByMeFish; // contain Ids for drone that currently scan the fish
	map<int, set<int> >			isDronesScannedByOpFish;

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

	/*fishes-target-points*/
	void	evaluate_fishes_targets(void);
	/*fishes-target-points*/

	/*fishes-to-kick-evaluate*/
	void	fishesEvaluatePossibleToKick(void);
	/*fishes-to-kick-evaluate*/

	/*drones-assignement+utils*/
	void	droneUpdateVelToKickOutTheTargetFish(Drone &drone);
	void	dronesAssingFishesToKickOut(void); // for testing strategie

	void	droneUpdateVelToScanTheTargetFish(Drone &drone);
	void	dronesAssingFishesToScan(void); // for testing strategie
	/*drones-assignement+utils*/

	/*uglys-simulation*/
	void		updateUglySpeed(Fish &ugly);
	void		snapUglyToZone(EVector &uglyPos);
	void		uglysSimulation(void);
	vector<int>	getClosestUglysIdFrom(Fish &ugly);
	vector<int>	uglysDroneIdTarget(Fish &ugly);
	/*uglys-simulation*/


	/*scores-evaluation*/
	void	scores_evaluate(void);
	/*scores-evaluation*/


	/*drone-avoidness*/
	bool	goodDroneVelocty(Drone &drone);
	void	dronesAvoidnes(Drone &drone);
	bool	isCoillisionBetwDroneUgly(Drone &drone, Fish &ugly);
	/*drone-avoidness*/


	/*drone-work*/
	void	droneUpdateVel(Drone &drone);
	void	droneLighEvaluateState(Drone &drone);
	/*drone-work*/


	/*debugs-functions*/
	void	debugVisibleSimulatedUglys(void);
	void	debugFishsVisibleSimulated(void);
	void	debugMyDroneState(void);
	void	debugSavedScore(void);
	void	debugUnsavedScore(void);
	void	debugScoring(void);
	void	debugFishsToKickAssinment(void);
	void	debugFishesPossibleToKick(void);
	/*debugs-functions*/

	void	solution();
};

