#include "../header.hpp"
#include "../includes/EVector.hpp"

/*start*/

EVector::EVector()
: x(0), y(0)
{
}

EVector::EVector(double _x, double _y)
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

	if (mag)
	{
		this->x /= mag;
		this->y /= mag;
	}
}

void	EVector::setMag(double _magnitude)
{
	this->normalize();
	(*this) *= _magnitude;
}

void	EVector::limit(double _magnitude)
{
	if (this->magnitude() > _magnitude)
	{
		this->setMag(_magnitude);
	}
}

EVector &EVector::operator=(const EVector &vect)
{
	this->x = vect.x;
	this->y = vect.y;
	return (*this);
}

EVector EVector::operator+(const EVector &vect)
{
	return EVector(this->x + vect.x, this->y + vect.y);
}

EVector EVector::operator-(const EVector &vect)
{
	return EVector(this->x - vect.x, this->y - vect.y);
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

EVector &EVector::operator*=(double value)
{
	this->x *= value;
	this->y *= value;
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

double calcDistance(EVector pointA, EVector pointB)
{
	return sqrt(
		(pointA.x - pointB.x) * (pointA.x - pointB.x) +
		(pointA.y - pointB.y) * (pointA.y - pointB.y)
	);
}