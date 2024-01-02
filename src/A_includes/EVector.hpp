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

	void	normalize();
	void	setMag(double _magnitude);
	void	limit(double _magnitude);
	double	magnitude() const; // distance from origin
	double	heading() const; // angle theta x,y

	void	roundme(void);
	bool	isZero(void) const;

	EVector &operator=(const EVector &vect);

	EVector operator+(const EVector &vect);
	EVector operator-(const EVector &vect);

	EVector &operator+=(const EVector &vect);
	EVector &operator-=(const EVector &vect);

	EVector &operator*=(int value);
	EVector &operator*=(double value);

	EVector &operator/=(double value);
	EVector operator/(double value);
};

istream &operator>>(istream &is, EVector &vect);
ostream &operator<<(ostream &os, const EVector &vect);

double calcDistance(EVector pointA, EVector pointB);

double	dotProduct(EVector a, EVector b);
EVector	vectorProjection(EVector vect, EVector path);
EVector	pointProjection(EVector point, EVector lineStartPoint, EVector lineEndPoint);
double	distanceBetweenPointAndLine(EVector point, EVector lineStartPoint, EVector lineEndPoint);
pair<EVector, EVector>	calcTheIntersctionReactangle(vector<pair<EVector, EVector>> &rectangles);
double	mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh);

