#pragma once

#include "../header.hpp"

/*start*/

struct Drone
{
	int		id;

	int		mode; // 0 scanne fishes type 3
				 // 1 save them
				// 2 scann the remaimning fishes
				// 3 save them

	EVector	pos;
	EVector	velocty;
	EVector	acceleration;

	int			emergency;
	int			light;
	int			battery;

	bool	isLightOn;

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
	void	snaptoDroneZone(void);

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
