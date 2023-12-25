#include "../header.hpp"
#include "../includes/Drone.hpp"

/*start*/

Drone::Drone()
{
	this->light = 1;
	this->velocty = EVector(0, 0);
	this->acceleration = EVector(0, 0);
	this->maxSpeed = 600;
	this->maxForce = 1e9;
	this->wanderTheta = ((M_PI * -1) / 2);
}

void	Drone::applyForce(EVector force)
{
	this->acceleration += force;
}

void	Drone::edges(void)
{
	if (this->pos.x <= 0 || this->pos.x >= 9999)
	{
		this->velocty.x *= -1;
	}

	if (this->pos.y <= 0 || this->pos.y >= 9999)
	{
		this->velocty.y *= -1;
	}

	this->updatePos();
}

void	Drone::updatePos(void)
{
	this->velocty += this->acceleration;
	this->velocty.setMag(this->maxSpeed);
	this->pos += this->velocty;
	this->acceleration *= 0;
}

EVector Drone::seekToPosForce(EVector target)
{
	EVector disered_vel = target - this->pos;

	disered_vel.setMag(this->maxSpeed);

	EVector force = disered_vel - this->velocty;

	return force;
}

EVector Drone::fleeFromPosForce(EVector target)
{
	EVector force = this->seekToPosForce(target);

	force *= -1;

	return force;
}

EVector Drone::arriveToPosForce(EVector target, double radius)
{
	EVector disered_vel = target - this->pos;

	double distance = disered_vel.magnitude();

	if (distance < radius)
	{
		double newMag = mapValue(distance, 0, radius, 0, this->maxSpeed);
		disered_vel.setMag(newMag);
	}
	else
	{
		disered_vel.setMag(this->maxSpeed);
	}

	EVector force = disered_vel - this->velocty;

	return force;
}

EVector	Drone::wanderForce(void)
{
	EVector wanderPoint = this->velocty;

	wanderPoint.setMag(500);

	wanderPoint += this->pos;

	double wanderRadius = 500;

	double theta = this->wanderTheta + this->velocty.heading();

	double x = wanderRadius * cos(theta);
	double y = wanderRadius * sin(theta);

	wanderPoint += EVector(x, y);

	EVector steer = (wanderPoint - this->pos);

	steer.setMag(this->maxSpeed);

	double displcaRange = 0.5;

	double r =  mapValue((rand()%100) - 100, -100, 99, 0, displcaRange*2) - displcaRange;

	this->wanderTheta += r;

	return (steer);
}

EVector Drone::avoidUglyForce(Fish &ugly)
{
	EVector UglyVel = this->pos - ugly.pos;

	UglyVel.setMag(100);

	EVector uglyPredectPos = ugly.pos + UglyVel;

	EVector toObstacle = this->pos - uglyPredectPos;

	double distance = toObstacle.magnitude();
	double obstacleRadius = 2300;

	if (0 < distance && distance < obstacleRadius)
	{
		toObstacle /= distance;
		return toObstacle;
	}

	return (EVector(0, 0));
}


/* Drone Comparison Operators OverLoads */
bool Drone::operator<(const Drone &other) const
{
	return (this->id < other.id);
}

bool Drone::operator<=(const Drone &other) const
{
	return (this->id <= other.id);
}

bool Drone::operator>(const Drone &other) const
{
	return (this->id > other.id);
}

bool Drone::operator>=(const Drone &other) const
{
	return (this->id >= other.id);
}

bool Drone::operator==(const Drone &other) const
{
	return (this->id == other.id);
}

istream &operator>>(istream &is, Drone &drone)
{
	is >> drone.id >> drone.pos >> drone.emergency >> drone.battery;
	cin.ignore();
	return (is);
}

ostream &operator<<(ostream &os, const Drone &drone)
{
	os << "DroneId: " << drone.id;
	os << " | Battery: " << drone.battery;
	os << " | Emergency: " << drone.emergency;
	os << " | " << drone.pos;
	os << " | ScannedCreaturesIDs: ";
	for (auto &id : drone.scannedCreatures)
		os << id << " ";
	return (os);
}
