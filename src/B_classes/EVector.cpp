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
	else
	{
		this->x = 0;
		this->y = 0;
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

void	EVector::roundme(void)
{
	this->x = (int)round(this->x);
	this->y = (int)round(this->y);
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

EVector &EVector::operator/=(double value)
{
	this->x /= value;
	this->y /= value;
	return (*this);
}

EVector EVector::operator/(double value)
{
	return (EVector(this->x / value, this->y / value));
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

double EVector::heading() const
{
	// Use atan2 to get the angle from the x-axis
	return atan2(this->y, this->x);
}

bool EVector::isZero(void) const
{
	return (this->x == 0 && this->y == 0);
}

double calcDistance(EVector pointA, EVector pointB)
{
	return sqrt(
		(pointA.x - pointB.x) * (pointA.x - pointB.x) +
		(pointA.y - pointB.y) * (pointA.y - pointB.y)
	);
}

double dotProduct(EVector a, EVector b)
{
	return (a.x * b.x) + (a.y * b.y);
}

EVector vectorProjection(EVector vect, EVector path)
{
	path.normalize();

	double spectre = dotProduct(vect, path);;

	path *= spectre;

	return (path);
}

EVector	pointProjection(EVector point, EVector lineStartPoint, EVector lineEndPoint)
{
	EVector	vectStartLineToPoint = point - lineStartPoint;

	EVector vectStartLineToEndLine = lineEndPoint - lineStartPoint;

	EVector vectProjection = vectorProjection(vectStartLineToPoint, vectStartLineToEndLine);

	return (lineStartPoint + vectProjection);
}

double distanceBetweenPointAndLine(EVector point, EVector lineStartPoint, EVector lineEndPoint)
{
	return (calcDistance(pointProjection(point, lineStartPoint, lineEndPoint), point));
}

pair<EVector, EVector> calcTheIntersctionReactangle(vector<pair<EVector, EVector>> &rectangles)
{
	if (rectangles.empty())
	{
		cerr << "No-information-for-that-fish." << endl;
		return {EVector(0, 0), EVector(9999, 9999)};
	}

	double maxLeft = rectangles[0].first.x;
	double maxTop = rectangles[0].first.y;
	double minRight = rectangles[0].second.x;
	double minBottom = rectangles[0].second.y;

	// Iterate through the rectangles to find the intersection
	for (const auto &rect : rectangles)
	{
		maxLeft = max(maxLeft, rect.first.x);
		maxTop = max(maxTop, rect.first.y);
		minRight = min(minRight, rect.second.x);
		minBottom = min(minBottom, rect.second.y);
	}

	// Check if there is a valid intersection
	if (maxLeft < minRight && maxTop < minBottom)
	{
		// Return the intersection rectangle
		return {EVector(maxLeft, maxTop), EVector(minRight, minBottom)};
	}
	else
	{
		cerr << "there-is-something-wrong-with-radar." << endl;
		return {EVector(0, 0), EVector(9999, 9999)};
	}
}

double mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh)
{
	double fromRange = fromHigh - fromLow;
	double toRange = toHigh - toLow;
	double scaledValue = (value - fromLow) / fromRange;

	return toLow + (scaledValue * toRange);
}

EVector	rotateVector(EVector vect, double angle)
{
	double x = vect.x;
	double y = vect.y;

	// Calculate rotated coordinates
	double xRotated = x * cos(angle) - y * sin(angle);
	double yRotated = x * sin(angle) + y * cos(angle);

	return EVector(xRotated, yRotated);
}
