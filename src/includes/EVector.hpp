#pragma once
# include "../header.hpp"

/*start*/

struct EVector
{
	int	x;
	int	y;

	EVector();
	EVector(int _x, int _y);
	EVector(const EVector &other);

	EVector &operator=(const EVector &vect);
	EVector &operator+=(const EVector &vect);
	EVector &operator*=(int value);
};

istream &operator>>(istream &is, EVector &vect);
ostream &operator<<(ostream &os, const EVector &vect);
