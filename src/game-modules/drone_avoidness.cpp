#include "../header.hpp"

/*start*/

struct Circle {
    float m_radius;
    float m_velocityX, m_velocityY;
    float m_positionX, m_positionY;
};

struct CollisionResult {
    bool isCollision;
    float collisionTime;
    float collisionPointX, collisionPointY;
};

bool checkCollision(const Circle& circleA, const Circle& circleB, float deltaTime)
{
	// Calculate relative velocity
	float relativeVelocityX = circleA.m_velocityX - circleB.m_velocityX;
	float relativeVelocityY = circleA.m_velocityY - circleB.m_velocityY;

	// Calculate relative position
	float relativePositionX = circleA.m_positionX - circleB.m_positionX;
	float relativePositionY = circleA.m_positionY - circleB.m_positionY;

	// Calculate coefficients for the quadratic equation
	float a = relativeVelocityX * relativeVelocityX + relativeVelocityY * relativeVelocityY;
	float b = 2.0f * (relativeVelocityX * relativePositionX + relativeVelocityY * relativePositionY);
	float c = relativePositionX * relativePositionX + relativePositionY * relativePositionY - pow(circleA.m_radius + circleB.m_radius, 2);

	// Calculate discriminant
	float discriminant = b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		// Calculate time of collision
		double t = (-b - sqrt(discriminant)) / (2.0f * a);

		if (t >= 0.0 && t <= 1.5)
			return true;

		// Handle the case of two possible collision points
		if (discriminant > 0) {
			// Calculate the second time of collision
			t = (-b + sqrt(discriminant)) / (2.0f * a);

			if (t >= 0.0 && t <= 1.5)
				return true;
		}
	}

	return false;
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

bool	Game::isCoillisionBetwDroneUgly(Drone &drone, Fish &ugly)
{
	double distance = ((drone.pos.x - ugly.pos.x) * (drone.pos.x - ugly.pos.x))
					+ ((drone.pos.y - ugly.pos.y) * (drone.pos.y - ugly.pos.y));

	double range = 500 + ((sqrt(distance) > 100.0) ? 20 : 2);

	if (distance <= range * range)
		return true;

	if (drone.velocty.x == 0 && drone.velocty.y == 0 &&
		ugly.velocty.x == 0 && ugly.velocty.y == 0)
	{
		return false;
	}

	EVector nextDronePos = drone.pos + drone.velocty;
	EVector nextUglyPos = ugly.pos + ugly.velocty;

	distance = ((nextDronePos.x - nextUglyPos.x) * (nextDronePos.x - nextUglyPos.x))
				+ ((nextDronePos.y - nextUglyPos.y) * (nextDronePos.y - nextUglyPos.y));

	if (distance <= (range + 5) * (range + 5))
		return true;

	Circle a, b;

	a.m_radius = range / 2;
	a.m_positionX = drone.pos.x;
	a.m_positionY = drone.pos.y;
	a.m_velocityX = drone.velocty.x;
	a.m_velocityY = drone.velocty.y;

	b.m_radius = range / 2;
	b.m_positionX = ugly.pos.x;
	b.m_positionY = ugly.pos.y;
	b.m_velocityX = ugly.velocty.x;
	b.m_velocityY = ugly.velocty.y;

	return (checkCollision(a, b, 1.0));
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
	}

	return (true);
}

void	Game::dronesAvoidnes(Drone &drone)
{
	if (drone.emergency) return ;

	double angle = 0;
	double shift = (2 * M_PI) / 3000;

	EVector	originVel = drone.velocty;
	bool	wayExist = false;

	while (angle < 6.30)
	{
		drone.velocty = rotateVector(originVel, angle);
		drone.velocty.roundme();

		double nx = (drone.pos.x + drone.velocty.x);
		double ny = (drone.pos.y + drone.velocty.y);

		if (nx >= 0 && nx <= 9999 && ny >= 0 && ny <= 9999)
		{
			if (this->goodDroneVelocty(drone))
			{
				wayExist = true;
				break;
			}
		}

		angle += shift;
	}

	if (!wayExist)
	{
		cerr << "noWay for drone: " << drone.id << endl;

		int uglyID = this->getClosestUgly(drone.pos);

		if (uglyID == -1) return ;

		Fish &ugly = this->getFishById(uglyID);

		drone.velocty = drone.pos - ugly.pos;
		drone.velocty.setMag(drone.maxSpeed);
		drone.velocty.roundme();
	}
}
