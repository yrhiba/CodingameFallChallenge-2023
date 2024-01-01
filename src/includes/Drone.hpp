#pragma once

#include "../header.hpp"

/*start*/

struct Drone
{
	Actions	action;

	int		id;

	int		mission; // || 0 scan fishes || 1 save fishes || 2 kick out fish || -1 nothing ||

	/*for-update-drone-vel*/
	EVector	TargetPos;

	// target fish to scan
	bool	assignedFishToScan; // true: must follow the target fish
	int		TargetFishToScan;

	// target fish to kick out
	bool	assignedFishToKick; // true: must kick out the target fish
	int		TargetFishToKick;

	// mode explore or go top for save the fishes;
	bool	mustGoToTop; // true need to go and save the fishes | false go to explore

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
