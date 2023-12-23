#pragma once

#include "../header.hpp"

/*start*/

struct Drone
{
	int		id;

	EVector	pos;
	EVector	velocty;
	EVector	acceleration;

	int		battery;
	int		emergency;
	int		myDrone;
	int		opDrone;
	int		maxSpeed;
	int		light;

	vector<int>					scannedCreatures;

	// creatureID : Direction
	vector<pair<int, string>>	creaturesDirection;

	// constructer
	Drone();

	void	applyForce(EVector force);
	void	edges(void);
	void	updatePos(void);


	bool operator<(const Drone &other) const;
	bool operator<=(const Drone &other) const;
	bool operator>(const Drone &other) const;
	bool operator>=(const Drone &other) const;
	bool operator==(const Drone &other) const;
};

istream &operator>>(istream &is, Drone &drone);
ostream &operator<<(ostream &os, const Drone &drone);
