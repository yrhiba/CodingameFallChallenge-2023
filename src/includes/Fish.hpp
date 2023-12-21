#pragma once
#include "../header.hpp"

/*start*/

struct Fish
{
	int		id;
	int		color;
	int		type;
	EVector	pos;
	EVector	prevPos;
	EVector velocty;
	EVector prevVelocty;
	int		scaned; // 0 : not-scanned || 1 : scanned
	int		dead;  // 0 : still alive || 1 : dead fish
	int		scannedByMe; // 0 | 1
	int		scannedByOp; // 0 | 1
	int		isVisible;  // 0 | 1

	/* TO DO: Simulate next move for this fish */
	/* 
		200 turn each turn we need to know each fish in wich postion
		gonna be !?;
	*/
	vector< int > simulate_next_pos_x; // TO DO
	vector< int > simulate_next_pos_y; // TO DO

	/* store distances between this fish and other drones  */
	// first: distance^2 | second: DroneId
	vector< pair<int, int> > fishDronePowerDistance;

	Fish();

	void setPos(EVector _pos);

	bool operator<(const Fish &other) const;
	bool operator<=(const Fish &other) const;
	bool operator>(const Fish &other) const;
	bool operator>=(const Fish &other) const;
	bool operator==(const Fish &other) const;
};

istream &operator>>(istream &is, Fish &fish);
ostream &operator<<(ostream &os, const Fish &fish);
