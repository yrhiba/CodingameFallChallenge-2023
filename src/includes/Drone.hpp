#pragma once

#include "../header.hpp"

/*start*/

struct Drone
{
	int		id; // FIX THE HOLE TURNS

	/*UPDATED EACH TURN*/
	EVector	pos;
	EVector	velocty;
	EVector	acceleration;
	EVector	TargetPos;
	/*UPDATED EACH TURN*/

	int			emergency; // GIVEN EACH TURN
	int			light; // GIVEN EACH TURN
	int			battery; // GIVEN EACH TURN
	int			isLightOn; // CALCULATED EACH TURN

	int			myDrone; // FIX THE HOLE TURNS
	int			opDrone; // FIX THE HOLE TURNS

	int			maxSpeed; // FIX THE HOLE TURNS
	double		maxForce; // FIX THE HOLE TURNS

	double		wanderTheta; // FIX THE HOLE TURNS

	vector<int>		scannedCreatures; // GIVEN EACH TURN 

	Actions		action; // GENRATE EACH TURN

	/*DRONE-MISSION*/
	// TO UPDATE EACH TURN //
	//#############//
	int			mission;
	deque<int>	queue_missions;
	// target fish to scan
	bool		assignedFishToScan;
	int			TargetFishToScan;
	// target fish to kick
	bool		assignedFishToKick;
	int			TargetFishToKick;
	// target save current scanneds
	bool		mustGoToTop;
	//#############//
	// TO UPDATE EACH TURN //
	/*DRONE-MISSION*/

	/*Ignored-for-the-moment-out-of-the-contest*/
	vector< pair<int, string> >	creaturesDirection;
	SingleLinePath				single_line_path;
	/*Ignored-for-the-moment-out-of-the-contest*/

	/*drone-updates*/
	void	updatePos(void);
	void	edges(void);
	void	snaptoDroneZone(void);
	/*drone-updates*/

	/*physique-engine|utils*/
	void	applyForce(EVector force);
	/*physique-engine|utils*/

	/*physique-engine|steering-behaviors(customized-for-the-bot-needs)*/
	EVector seekToPosForce(EVector target);
	EVector fleeFromPosForce(EVector target);
	EVector arriveToPosForce(EVector target, double radius);
	EVector avoidUglyForce(Fish &ugly);
	EVector wanderForce(void);
	EVector followSingleLinePathForce(void);
	/*phisique-engine|steering-behaviors*/

	/*operators-overlod*/
	bool operator<(const Drone &other) const;
	bool operator<=(const Drone &other) const;
	bool operator>(const Drone &other) const;
	bool operator>=(const Drone &other) const;
	bool operator==(const Drone &other) const;
	/*operators-overlod*/

	/*constructer*/
	Drone();
	/*constructer*/
};

istream &operator>>(istream &is, Drone &drone);
ostream &operator<<(ostream &os, const Drone &drone);
