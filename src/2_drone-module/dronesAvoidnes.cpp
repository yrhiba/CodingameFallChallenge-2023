#include "header.hpp"

/*start*/

struct Circle {
	float m_radius;
	float m_velocityX, m_velocityY;
	float m_positionX, m_positionY;
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

bool	Game::isCoillisionBetwDroneUgly(Drone &drone, Fish &ugly, double range = 540)
{
	double distance = ((drone.pos.x - ugly.pos.x) * (drone.pos.x - ugly.pos.x))
					+ ((drone.pos.y - ugly.pos.y) * (drone.pos.y - ugly.pos.y));

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

	if (distance <= range * range)
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

bool	Game::goodDroneVelocty(Drone &drone, double range = 540)
{
	vector<int> &uglysId = this->typeFishes[-1];

	for (int &uglyId : uglysId)
	{
		Fish &ugly = this->getFishById(uglyId);

		if (ugly.visibleAtTurn == -1) continue;

		if (isCoillisionBetwDroneUgly(drone, ugly, range))
		{
			drone.action.uglyToAvoid.insert(ugly.id);
			return (false);
		}

		Drone	nextDrone;
		Fish	nextUgly;

		nextDrone.pos = drone.pos + drone.velocty;
		nextUgly.pos = ugly.pos + ugly.velocty;

		nextDrone.velocty = nextUgly.velocty = nextDrone.pos - nextUgly.pos;

		nextDrone.velocty.setMag(600);
		nextUgly.velocty.setMag(540);

		nextDrone.velocty.roundme();
		nextUgly.velocty.roundme();

		if (isCoillisionBetwDroneUgly(nextDrone, nextUgly, range))
			return (false);
	}

	return (true);
}

bool	Game::dronesAvoidnes(Drone &drone, double range = 540)
{
	if (drone.emergency) return (false);
	double angle = 0;
	double shift = (2 * M_PI) / 3000;
	EVector	firstVel = EVector(-1e9, -1e9);
	EVector	secondVel = EVector(-1e9, -1e9);
	EVector	originVel = drone.velocty;
	bool	wayExist = false;
	while (angle < 3.15)
	{
		drone.velocty = rotateVector(originVel, angle);
		drone.velocty.roundme();

		double nx = (drone.pos.x + drone.velocty.x);
		double ny = (drone.pos.y + drone.velocty.y);

		if (nx >= 0 && nx <= 9999 && ny >= 0 && ny <= 9999)
		{
			if (this->goodDroneVelocty(drone, range))
			{
				firstVel = drone.velocty;
				wayExist = true;
				break;
			}
		}

		angle += shift;
	}
	angle = 0;
	while (angle < 3.15)
	{
		drone.velocty = rotateVector(originVel, angle * -1);
		drone.velocty.roundme();

		double nx = (drone.pos.x + drone.velocty.x);
		double ny = (drone.pos.y + drone.velocty.y);

		if (nx >= 0 && nx <= 9999 && ny >= 0 && ny <= 9999)
		{
			if (this->goodDroneVelocty(drone, range))
			{
				secondVel = drone.velocty;
				wayExist = true;
				break;
			}
		}

		angle += shift;
	}
	if (!wayExist)
	{
		if (abs(drone.velocty.magnitude() - 600) > 0.5)
		{
			if (drone.velocty.isZero()) 
			{
				drone.velocty = EVector((rand()%10)+1, (rand()%10)+1);
			}
			drone.velocty.setMag(drone.maxSpeed);
			drone.velocty.roundme();
			return (this->dronesAvoidnes(drone, range));
		}
		else
		{
			// go to top to win some time.
			drone.velocty = EVector(0, -600);
			drone.velocty.setMag(drone.maxSpeed);
			drone.velocty.roundme();
			return (false);
		}
	}
	else
	{
		if (secondVel.x == -1e9)
		{
			drone.velocty = firstVel;
		}
		else if (firstVel.x == -1e9)
		{
			drone.velocty = secondVel;
		}
		else
		{
			EVector target = drone.pos + originVel;
			if (calcDistance(target, drone.pos + firstVel)
				<= calcDistance(target, drone.pos + secondVel))
			{
				drone.velocty = firstVel;
			}
			else
			{
				drone.velocty = secondVel;
			}
		}
	}
	return (true);
}
