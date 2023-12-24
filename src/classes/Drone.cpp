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

	for (int i = 0; i < 2; i++)
		this->updatePos();
}

void	Drone::updatePos(void)
{
	this->velocty += this->acceleration;
	this->velocty.limit(this->maxSpeed);
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
