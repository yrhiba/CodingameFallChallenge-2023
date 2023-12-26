#pragma once

#include "../header.hpp"

/*start*/

struct Drone
{
	int		id;

	EVector	pos;
	EVector	velocty;
	EVector	acceleration;

	// to convert to array of MAX_GAME_TURN
	int		battery;
	int		emergency;
	int		light;


	int		myDrone;
	int		opDrone;

	int		maxSpeed;
	double	maxForce;

	double	wanderTheta;

	SingleLinePath	single_line_path;

	vector<int>		scannedCreatures;

	// creatureID : Direction
	vector< pair<int, string> >	creaturesDirection;

	// constructer
	Drone();

	void	applyForce(EVector force);
	void	edges(void);
	void	updatePos(void);

	EVector seekToPosForce(EVector target);
	EVector fleeFromPosForce(EVector target);
	EVector arriveToPosForce(EVector target, double radius);
	EVector avoidUglyForce(Fish &ugly);
	EVector wanderForce(void);
	EVector followSingleLinePathForce(void);

	bool operator<(const Drone &other) const;
	bool operator<=(const Drone &other) const;
	bool operator>(const Drone &other) const;
	bool operator>=(const Drone &other) const;
	bool operator==(const Drone &other) const;
};

istream &operator>>(istream &is, Drone &drone);
ostream &operator<<(ostream &os, const Drone &drone);
