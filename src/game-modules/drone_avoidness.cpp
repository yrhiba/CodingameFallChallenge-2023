#include "../header.hpp"

/*start*/

EVector	rotateVector(EVector vect, double angle)
{
	double x = vect.x;
	double y = vect.y;

	// Calculate rotated coordinates
	double xRotated = x * cos(angle) - y * sin(angle);
	double yRotated = x * sin(angle) + y * cos(angle);

	return EVector(xRotated, yRotated);
}


bool Game::getCollision(Drone &drone, Fish& ugly)
{
        // Check instant collision
        pair <int ,int> next_stp = {drone.pos.x + drone.velocty.x, drone.pos.y + drone.velocty.y};

        double DroneSpeedX = drone.velocty.x;
        double DroneSpeedY = drone.velocty.y;

		double distance = (drone.pos.x + drone.velocty.x - ugly.pos.x) * (drone.pos.x - ugly.pos.x) 
					+ ((drone.pos.y - ugly.pos.y) * (drone.pos.y - ugly.pos.y));

		double range = 500;

		if (distance <= range * range)
			return true;

		double distanceBetweenNextPosUgly = 
			(next_stp.first - ugly.pos.x) * (next_stp.first - ugly.pos.x) +
			(next_stp.second - ugly.pos.y) * (next_stp.second - ugly.pos.y);



		if (distanceBetweenNextPosUgly <= 500 * 500) {
			return true;
		}

		if (!ugly.velocty.x && !ugly.velocty.y && !DroneSpeedX && !DroneSpeedY) return false;

		// Change referencial
		double x = ugly.pos.x, y = ugly.pos.y, ux = drone.pos.x, uy = drone.pos.y;
		double x2 = x - ux, y2 = y - uy;
		double r2 = 500;

		double vx2 = ugly.velocty.x - DroneSpeedX, vy2 = ugly.velocty.y - DroneSpeedY;
		double a = vx2 * vx2 + vy2 * vy2;
		if ( a <= 0.0) return false;
		double b = 2.0 * (x2 * vx2 + y2 * vy2);
		double c = x2 * x2 + y2 * y2 - r2 * r2;
		double delta = b * b - 4.0 * a * c;
		if (delta < 0.0) return false;
		double t = (-b - sqrt(delta)) / (2.0 * a);
		if (t <= 0.0) return false; 
		if (t > 1.0) return false;
		return true;
}

bool	Game::isCoillisionBetwDroneUgly(Drone &drone, Fish &ugly)
{
	double distance = (drone.pos.x + drone.velocty.x - ugly.pos.x) * (drone.pos.x - ugly.pos.x) 
					+ ((drone.pos.y - ugly.pos.y) * (drone.pos.y - ugly.pos.y));

	double range = 505;

	if (distance <= range * range)
		return true;

	if (drone.velocty.x == 0 && drone.velocty.y == 0 &&
		ugly.velocty.x == 0 && ugly.velocty.y == 0)
	{
		return false;
	}

	double x = ugly.pos.x;
	double y = ugly.pos.y;
	double ux = drone.pos.x;
	double uy = drone.pos.y;


	double x2 = x - ux;
	double y2 = y - uy;
	double r2 = range;
	double vx2 = ugly.velocty.x - drone.velocty.x;
	double vy2 = ugly.velocty.y - drone.velocty.x;

	double a = vx2 * vx2 + vy2 * vy2;

	if (a <= 0.0) {
		return false;
	}

	double b = 2.0 * (x2 * vx2 + y2 * vy2);
	double c = x2 * x2 + y2 * y2 - r2 * r2;
	double delta = b * b - 4.0 * a * c;

	if (delta < 0.0) {
		return false;
	}

	double t = (-b - sqrt(delta)) / (2.0 * a);

	if (t <= 0.0) {
		return false;
	}

	if (t > 1.0) {
		return false;
	}

	return true;
}

bool	Game::goodDroneVelocty(Drone &drone)
{
	vector<int> &uglysId = this->typeFishes[-1];

	for (int &uglyId : uglysId)
	{
		Fish &ugly = this->getFishById(uglyId);

		if (!ugly.isVisible) continue;

		if (isCoillisionBetwDroneUgly(drone, ugly))
			return (false);
		// if (this->getCollision(drone, ugly))
		// 	return (false);
	}

	return (true);
}

void	Game::dronesAvoidnes(Drone &drone)
{
	double angle = 0;
	double shift = (2 * M_PI) / 360;

	EVector	originVel = drone.velocty;
	bool	wayExist = false;

	while (angle < 6.30)
	{
		drone.velocty = rotateVector(originVel, angle);
		drone.velocty.roundme();

		double nx = (drone.pos.x + drone.velocty.x);
		double ny = (drone.pos.y + drone.velocty.y);

		if (nx >= 0 && nx <= 9999 && ny >= 0 && ny <= 9999
			&& this->goodDroneVelocty(drone))
		{
			wayExist = true;
			break;
		}

		angle += shift;
	}

	if (!wayExist)
	{
		cerr << "noWay for drone: " << drone.id << endl;
	}
}
