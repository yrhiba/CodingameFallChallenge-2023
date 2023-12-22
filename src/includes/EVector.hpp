#pragma once
# include "../header.hpp"

/*start*/

struct EVector
{
	double	x;
	double	y;

	EVector();
	EVector(double _x, double _y);
	EVector(const EVector &other);

	double	magnitude() const;
	void	normalize();
	void	setMag(double _magnitude);
	void	limit(double _magnitude);

	EVector &operator=(const EVector &vect);

	EVector operator+(const EVector &vect);
	EVector operator-(const EVector &vect);

	EVector &operator+=(const EVector &vect);
	EVector &operator-=(const EVector &vect);

	EVector &operator*=(int value);
	EVector &operator*=(double value);
};


istream &operator>>(istream &is, EVector &vect);
ostream &operator<<(ostream &os, const EVector &vect);
