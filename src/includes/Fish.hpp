#pragma once
#include "../header.hpp"

/*start*/

struct Fish
{
	int id;
	int color;
	int type;
	int x;
	int y;
	int prev_x; // previous x position
	int prev_y; // previous y position
	int vx; // speed direction x-axis 
	int vy; // speed direction y-axis
	int prev_vx;
	int prev_vy;
	int scaned; // 0 : not-scanned || 1 : scanned
	int dead;  // 0 : still alive || 1 : dead fish
	int scannedByMe; // 0 | 1
	int scannedByOp; // 0 | 1
	int isVisible;  // 0 | 1

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

	void setPos(int _x, int _y);

	bool operator<(const Fish &other) const;
	bool operator<=(const Fish &other) const;
	bool operator>(const Fish &other) const;
	bool operator>=(const Fish &other) const;
	bool operator==(const Fish &other) const;
};

istream &operator>>(istream &is, Fish &fish);
ostream &operator<<(ostream &os, const Fish &fish);
