#pragma once
#include "header.hpp"

/*start*/

# define DEFAULT_PATH_RADIUS 700

# define FORWARD_DIR 1
# define BACKWARD_DIR -1

struct SingleLinePath
{
	EVector	pointA;
	EVector	pointB;
	double	radius;
	int		direction;
	bool	reacheTheEnd;

	SingleLinePath();
	SingleLinePath(const SingleLinePath &other);
	SingleLinePath(EVector _pointA, EVector _pointB);
	SingleLinePath(EVector _pointA, EVector _pointB, double radius);

	void	setDirection(int _direction);
	void	reverseDirection(void);
	void	reset(void);
	bool	isFinish() const;
};
