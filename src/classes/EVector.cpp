#include "../header.hpp"
#include "../includes/EVector.hpp"

/*start*/

EVector::EVector(int _x, int _y)
	: x(_x), y(_y)
{
}

EVector::EVector(const EVector &other)
: x(other.x), y(other.y)
{
}

EVector &EVector::operator=(const EVector &vect)
{
	this->x = vect.x;
	this->y = vect.y;
	return (*this);
}

EVector &EVector::operator+=(const EVector &vect)
{
	this->x += vect.x;
	this->y += vect.y;
	return (*this);
}

istream &operator>>(istream &is, EVector &vect)
{
	is >> vect.x >> vect.y;
	return is;
}

ostream &operator<<(ostream &os, const EVector &vect)
{
	os << "(" << vect.x << "," << vect.y << ")";
	return (os);
}
