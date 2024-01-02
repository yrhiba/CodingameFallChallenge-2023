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
	int		scannedByMe; // UPDATED EACH TURN
	int		scannedByOp; // UPDATED EACH TURN
	int		isVisible; // UPDATED EACH TURN
	int		visibleAtTurn; // UPDATED EACH TURN
	bool	availableToKick; // UPDATED EACH TURN
	bool	availlableToscan; // UPDATED EACH TURN
	/*fish-flags*/

	/*for-fishes-evaluations*/
	pair<EVector, EVector>				existZone; // UPDATED EACH TURN
	vector< pair<EVector, EVector> >	existZones; // UPDATED EACH TURN
	EVector								targetPointToScan; // UPDATED EACH TURN
	/*for-fishes-evaluations*/

	/*sters*/
	void	setPos(EVector _pos);
	/*sters*/

	/*operators-overlod*/
	bool operator<(const Fish &other) const;
	bool operator<=(const Fish &other) const;
	bool operator>(const Fish &other) const;
	bool operator>=(const Fish &other) const;
	bool operator==(const Fish &other) const;
	/*operators-overlod*/

	/*constructor*/
	Fish();
	/*constructor*/
};

istream &operator>>(istream &is, Fish &fish);
ostream &operator<<(ostream &os, const Fish &fish);
