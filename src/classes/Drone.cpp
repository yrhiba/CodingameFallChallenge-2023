#include "../header.hpp"
#include "../includes/Drone.hpp"

/*start*/

Drone::Drone()
{
	/*init-data*/
	this->alreadyAssignedToSeekAFish = false;
	this->TargetFish = -1;
	this->TargetPos = EVector(0, 0);
	this->emergency = 0;
	this->light = 0;
	this->velocty = EVector(0, 0);
	this->acceleration = EVector(0, 0);
	this->maxSpeed = 600;
	this->maxForce = 1e9;
	this->wanderTheta = ((M_PI * -1) / 2);
	this->isLightOn = false;
}

void	Drone::applyForce(EVector force)
{
	this->acceleration += force;
}

void	Drone::edges(void)
{
	EVector nextDronePos = this->pos + this->velocty;

	if ((nextDronePos.x < 0 && nextDronePos.x < this->pos.x) || 
		(nextDronePos.x > 9999 && nextDronePos.x > this->pos.x)
	)
	{
		this->velocty.x *= -1;
	}

	if ((nextDronePos.y < 0 && nextDronePos.y < this->pos.y) || 
		(nextDronePos.y > 9999 && nextDronePos.y > this->pos.y)
	)
	{
		this->velocty.y *= -1;
	}
}

void	Drone::snaptoDroneZone(void)
{
	if (this->pos.x < 0)
		this->pos.x = 0;
	if (this->pos.y < 0)
		this->pos.y = 0;

	if (this->pos.x > 9999)
		this->pos.x = 9999;
	if (this->pos.y > 9999)
		this->pos.y = 9999;
}

void	Drone::updatePos(void)
{
	this->acceleration.roundme();
	this->velocty += this->acceleration;
	this->velocty.setMag(this->maxSpeed);
	this->velocty.roundme();
	this->pos += this->velocty;
	this->snaptoDroneZone();
	this->velocty *= 0;
	this->acceleration *= 0;
}

EVector Drone::seekToPosForce(EVector target)
{
	EVector disered_vel = target - this->pos;

	disered_vel.setMag(this->maxSpeed);
	disered_vel.roundme();

	return disered_vel;
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

EVector Drone::followSingleLinePathForce(void)
{
	SingleLinePath &path = this->single_line_path;

	if (path.isFinish())
	{
		return (EVector(0, 0));
	}

	EVector &targetEnd = (path.direction == FORWARD_DIR) ? path.pointB : path.pointA;

	if (calcDistance(this->pos, targetEnd) <= 500)
	{
		path.reacheTheEnd = true;
		return (EVector(0, 0));
	}

	// step 1: predictied drone position point
	EVector predictedPoint = this->pos;

	// step 2: project the point into the line
	EVector projectedPoint = pointProjection(predictedPoint, path.pointA, path.pointB);

	// step 4: choes direction
	EVector direction = EVector(0, 0);

	if (path.direction == FORWARD_DIR)
	{
		direction = path.pointB - path.pointA;
	}
	else
	{
		direction = path.pointA - path.pointB;
	}

	direction.setMag(300);
	direction.roundme();

	// step 5: calculate the target position
	EVector target = projectedPoint + direction;

	return this->seekToPosForce(target);
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
