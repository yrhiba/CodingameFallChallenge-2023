#include "../includes/SingleLinePath.hpp"

/*start*/

SingleLinePath::SingleLinePath()
:
pointA(EVector(0, 0)),
pointB(EVector(MAP_SIZE, MAP_SIZE)),
radius(DEFAULT_PATH_RADIUS),
direction(FORWARD_DIR),
reacheTheEnd(false)
{
}

SingleLinePath::SingleLinePath(const SingleLinePath &other)
: pointA(other.pointA),
pointB(other.pointB),
radius(other.radius),
direction(FORWARD_DIR),
reacheTheEnd(false)
{
}

SingleLinePath::SingleLinePath(EVector _pointA, EVector _pointB)
: pointA(_pointA),
pointB(_pointB),
radius(DEFAULT_PATH_RADIUS),
direction(FORWARD_DIR),
reacheTheEnd(false)
{
}

SingleLinePath::SingleLinePath(EVector _pointA, EVector _pointB, double _radius)
: pointA(_pointA),
pointB(_pointB),
radius(_radius),
direction(FORWARD_DIR),
reacheTheEnd(false)
{
}

void SingleLinePath::setDirection(int _direction)
{
	direction = _direction;
}

void SingleLinePath::reverseDirection(void)
{
	direction *= -1;
}

void	SingleLinePath::reset(void)
{
	this->reacheTheEnd = false;
}

bool	SingleLinePath::isFinish() const
{
	return this->reacheTheEnd;
}
