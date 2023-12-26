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
	EVector	nextPos;

	EVector	velocty;
	EVector	prevVelocty;
	EVector	nextVelocty;

	int		scaned; // 0 : not-scanned || 1 : scanned
	int		dead;  // 0 : still alive || 1 : dead fish
	int		scannedByMe; // 0 | 1
	int		scannedByOp; // 0 | 1
	int		isVisible;  // 0 | 1

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
