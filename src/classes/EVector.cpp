#include "../header.hpp"
#include "../includes/EVector.hpp"

/*start*/

EVector::EVector()
: x(0), y(0)
{
}

EVector::EVector(int _x, int _y)
	: x(_x), y(_y)
{
}

EVector::EVector(const EVector &other)
: x(other.x), y(other.y)
{
}

double EVector::magnitude() const
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}

void	EVector::normalize()
{
	double mag = this->magnitude();

	this->x = round(this->x / mag);
	this->y = round(this->x / mag);
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

EVector &EVector::operator-=(const EVector &vect)
{
	this->x -= vect.x;
	this->y -= vect.y;
	return (*this);
}

EVector &EVector::operator*=(int value)
{
	this->x *= value;
	this->y *= value;
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
