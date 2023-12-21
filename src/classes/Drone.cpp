

/*start*/

struct Drone 
{
	int id;
	int x;
	int y;
	int battery;
	int emergency;
	int myDrone; // 0 (oponnets-drone) or 1 (my-drone)
	int opDrone;

	string						direction;

	vector<int>					scannedCreatures;
	vector<pair<int, string>>	creaturesDirection; // creatureID : Direction

	Drone()
	{
		this->direction = ((rand()%1) ? "BL" : "BR");
	}

	/* Drone Comparison Operators OverLoads */
	bool operator<(const Drone &other)
	{
		return (this->id < other.id);
	}
	bool operator<=(const Drone &other)
	{
		return (this->id <= other.id);
	}
	bool operator>(const Drone &other)
	{
		return (this->id > other.id);
	}
	bool operator>=(const Drone &other)
	{
		return (this->id >= other.id);
	}
	bool operator==(const Drone &other)
	{
		return (this->id == other.id);
	}
};

istream &operator>>(istream &is, Drone &drone)
{
	is >> drone.id >> drone.x >> drone.y >> drone.emergency >> drone.battery;
	cin.ignore();
	return (is);
}

ostream &operator<<(ostream &os, const Drone &drone)
{
	os << "DroneId: " << drone.id;
	os << " | Battery: " << drone.battery;
	os << " | Emergency: " << drone.emergency;
	os << " | MyDrone: " << drone.myDrone;
	os << " | OpDrone: " << drone.opDrone;
	os << " | (" << drone.x << "," << drone.y << ")";
	os << " | ScannedCreaturesIDs: ";
	for (auto &id : drone.scannedCreatures)
		os << id << " ";
	os << " | Direction: " << drone.direction;
	return (os);
}