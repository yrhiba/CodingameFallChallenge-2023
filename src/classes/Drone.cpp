#include "../header.hpp"
#include "../includes/Drone.hpp"

/*start*/

Drone::Drone()
{
	this->light = 1;
	this->velocty = EVector(rand()%2000 - 1000, rand()%1000);
	this->velocty.setMag(600);
	this->acceleration = EVector(0, 0);
	this->maxSpeed = 600;
	this->direction = ((rand()%1) ? "BL" : "BR");
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
