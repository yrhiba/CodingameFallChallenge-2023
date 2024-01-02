#pragma once
#include "../header.hpp"

/*start*/

struct Fish
{
	int		id; // FIX THE HOLE TURNS
	int		color; // FIX THE HOLE TURNS
	int		type; // FIX THE HOLE TURNS

	EVector	pos; // UPDATED EACH TURN
	EVector	velocty; // UPDATED EACH TURN
	EVector	nextPos; // UPDATED EACH TURN

	/*fish-flags*/
	int		scaned; // UPDATED EACH TURN
	int		dead; // UPDATED EACH TURN
	int		deadNextTurn; // UPDATED EACH TURN
	int		scannedByMe; // UPDATED EACH TURN
	int		scannedByOp; // UPDATED EACH TURN
	int		unsavedScanedByMe; // UPDATED EACH TURN
	int		unsavedScanedByOP; // UPDATED EACH TURN
	int		visibleAtTurn; // UPDATED EACH TURN
	bool	availableToKick; // UPDATED EACH TURN
	bool	availlableToscan; // UPDATED EACH TURN
	/*fish-flags*/

	/*drones-currently-scan-the-fish*/
	set<int>	dronesScan; // UDPATED EACH TURN
	set<int>	myDronesScan; // UDPATED EACH TURN
	set<int>	opDronesScan; // UDPATED EACH TURN
	/*drones-currently-scan-the-fish*/

	/*for-fishes-evaluations*/
	pair<EVector, EVector>				existZone; // UPDATED EACH TURN
	vector< pair<EVector, EVector> >	existZones; // UPDATED EACH TURN
	EVector								estimationPosition; // UPDATED EACH TURN
	/*for-fishes-evaluations*/

	/*snap-fish-into-fihsType-Zone*/
	void	snapToZone(void);
	/*snap-fish-into-fihsType-Zone*/

	/*sters*/
	void	setNextPos(void);
	void	setStandardFishZone(void);
	void	setAvaillabilty(void);
	/*sters*/

	/*Push-Exist-Zone*/
	void	pushExistZone(EVector pos, string radar);
	/*Push-Exist-Zone*/

	/*check-dead-for-next-turn*/
	bool	isDeadNextTurn(void);
	/*check-dead-for-next-turn*/

	/*estimate-possible-position*/
	void	extimatePossiblePosition(void);
	/*estimate-possible-position*/

	/*operators-overlod*/
	bool operator<(const Fish &other) const;
	bool operator<=(const Fish &other) const;
	bool operator>(const Fish &other) const;
	bool operator>=(const Fish &other) const;
	bool operator==(const Fish &other) const;
	/*operators-overlod*/

	/*initialize-setup-turn*/
	void	initializeSetupGameData(void);
	/*initialize-setup-turn*/
	/*initialize-each-turn*/
	void	initializeAndSetupTurnData(void);
	/*initialize-each-turn*/
};

istream &operator>>(istream &is, Fish &fish);
ostream &operator<<(ostream &os, const Fish &fish);
