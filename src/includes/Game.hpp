#pragma once
#include "../header.hpp"
#include "../includes/Drone.hpp";
#include "../includes/Fish.hpp"

/*start*/

struct Game
{
	int	game_turn; // INCREMENTED EACH TURN

	int	creature_count; // FIX ALL THE GAME
	int	creature_visible_count; // CALCULATED EACH TURN

	int	my_score; // GIVEN EACH TURN
	int	my_scan_count; // GIVEN EACH TURN
	int	my_drone_count; // FIX ALL THE GAME

	int	op_score; // GIVEN EACH TURN
	int	op_scan_count; // GIVEN EACH TURN
	int	op_drone_count; // FIX ALL THE GAME

	// Fishes Informations
	vector<Fish>				allFishes; // FIX ALL THE GAME
	map<int, vector<int>>		typeFishes; // FIX ALL THE GAME

	// Drones Informations
	vector<Drone>				allDrones; // FIX ALL THE GAME
	vector<int>					myDrones; // FIX ALL THE GAME
	vector<int>					opponentsDrones; // FIX ALL THE GAME

	// EVALUATED Informations - about the fishes
	set<int>					fishsPossibleToKick; // CLEAR EACH TURN
	set<int>					fishsPossibleToScan; // CLEAR EACH TURN
	set<int>					fishsPossibleToKickType[3]; // CLEAR EACH TURN
	set<int>					fishsPossibleToScanType[3]; // CLEAR EACH TURN

	// FISHS FLAGS ANSERING QUESTION FOR DOUBLE SAVETY CHECK
	map<int, bool>				isScannedFish; // CLEARED EACH TURN
	map<int, bool>				isScannedByMeFish; // CLEARED EACH TURN
	map<int, bool>				isScannedByOpFish;	// CLEARED EACH TURN
	map<int, set<int> >			isDronesScannedByMeFish; // CLEARED EACH TURN
	map<int, set<int> >			isDronesScannedByOpFish; // CLEARED EACH TURN
	map<int, bool>				isDeadFish; // CLEARD EACH TURN

	void initTurn( void );

	/*game-geters*/
	Fish	&getFishById(int fishId);
	Drone	&getDroneById(int droneId);
	int		getClosestUgly(EVector pos);
	int		getClosestDroneIdFromPos(EVector pos);
	int		getClosestVisibleFishNotScannedYet(EVector pos);
	/*game-geters*/

	/*fishes-target-points*/
	void	evaluate_fishes_targets(void);
	/*fishes-target-points*/

	/*fishes-to-scan/kick-evaluate*/
	void	fishesEvaluatePossibleToKick(void);
	void	fishesEvaluatePossibleToScan(void);
	/*fishes-to-scan/kick-evaluate*/

	/*drones-assignement+utils*/
	void	droneUpdateVelToKickOutTheTargetFish(Drone &drone);
	void	dronesAssingFishesToKickOut(void); // for testing strategie

	void	dronesAssignFishToScanWithType(int fishesType);
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

	/*fishes-simulatio*/
	void		fishesSimulation(void);
	/*fishes-simulatio*/

	/*scores-evaluation*/
	void	scores_evaluate(void);
	/*scores-evaluation*/

	/*drone-avoidness*/
	bool	isCoillisionBetwDroneUgly(Drone &drone, Fish &ugly);
	bool	goodDroneVelocty(Drone &drone);
	void	dronesAvoidnes(Drone &drone);
	/*drone-avoidness*/

	/*drone-work*/
	void	droneUpdateVel(Drone &drone);
	void	droneLighEvaluateState(Drone &drone);
	/*drone-work*/

	/*debugs-functions*/
	void	debugVisibleSimulatedUglys(void);
	void	debugFishsVisibleSimulated(void);
	void	debugMyDroneState(void);
	void	debugFishsToKickAssinment(void);
	void	debugFishesPossibleToKick(void);
	void	debugFishesPossibleToScan(void);
	void	debugDronesActions(void);
	/*debugs-functions*/

	/*game-turn-clear*/
	void	clearGamePreviousTurnData(void);
	void	initializeAndUpdateTurnData(void);
	void	initializeAndUpdateFishesTurnData(void);
	/*game-turn-clear*/

	/*game-reads-first-turn*/
	void	readSetupCreatures(void);
	void	readSetupDrones(void);
	/*game-reads-first-turn*/

	/*game-reads-each-turn*/
	void readScores(void);
	void readScannedCreatures( void );
	void readDrones(void);
	void readDronesCurrentScan( void );
	void readVisibleCreatures( void );
	void readRadarInfo(void);
	/*game-reads-each-turn*/

	void	solution();

	/* constructer */
	Game()
	{
		this->game_turn = -1;
	}
	/* constructer */
};

