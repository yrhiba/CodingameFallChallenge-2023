#include "../header.hpp"

/*start*/

void	Game::snapUglyToZone(EVector &uglyPos)
{
	if (uglyPos.x < 0)
		uglyPos.x = 0;

	if (uglyPos.y < 0)
		uglyPos.y = 0;

	if (uglyPos.y > 9999)
		uglyPos.y = 9999;

	if (uglyPos.y < 2500)
		uglyPos.y = 2500;
}

vector<int>		Game::uglysDroneIdTarget(Fish &ugly)
{
	vector<int>	droneIds;
	int			droneDis = -1;

	for (Drone &drone : this->allDrones)
	{
		if (drone.emergency) continue;

		double range = drone.isLightOn ? 2000 : 800;
		double distance =	(drone.pos.x - ugly.pos.x) * (drone.pos.x - ugly.pos.x) +
							(drone.pos.y - ugly.pos.y) * (drone.pos.y - ugly.pos.y);

		if (distance <= (range * range))
		{
			if (droneDis == -1)
			{
				droneIds.push_back(drone.id);
				droneDis = distance;
			}
			else if (distance < droneDis)
			{
				droneIds = vector<int>(1, drone.id);
				droneDis = distance;
			}
			else if (distance == droneDis)
			{
				droneIds.push_back(drone.id);
			}
		}
	}

	return (droneIds);
}

vector<int>	Game::getClosestUglysIdFrom(Fish &ugly)
{
	vector<int>	uglyIds;
	double		uglyDis = -1;

	vector<int> &allUglys = this->typeFishes[-1];

	for (int &curUglyId : allUglys)
	{
		if (curUglyId == ugly.id)	continue;

		Fish &curUgly = this->getFishById(curUglyId);

		double range = 600;
		double distance = calcDistance(curUgly.pos, ugly.pos);

		if (distance <= range)
		{
			if (uglyDis == -1)
			{
				uglyIds.push_back(curUgly.id);
				uglyDis = distance;
			}
			else if (distance < uglyDis)
			{
				uglyIds = vector<int>(1, curUgly.id);
				uglyDis = distance;
			}
			else if (distance == uglyDis)
			{
				uglyIds.push_back(curUgly.id);
			}
		}
	}

	return (uglyIds);
}

void	Game::uglysSimulation(void)
{
	vector<int> &allUglys = this->typeFishes[-1];

	for (int UglyId : allUglys)
	{
		Fish &ugly = this->getFishById(UglyId);

		if (ugly.visibleAtTurn == -1) continue;

		ugly.velocty.roundme();
		ugly.pos += ugly.velocty;
		this->snapUglyToZone(ugly.pos);
	}

	for (int UglyId : allUglys)
	{
		Fish &ugly = this->getFishById(UglyId);
		if (!ugly.isVisible) continue;
		if (ugly.visibleAtTurn == -1)
		{
			ugly.visibleAtTurn = this->game_turn;
			continue;
		}

		vector<int> dronesId = this->uglysDroneIdTarget(ugly);

		if (dronesId.empty())
		{
			ugly.velocty.limit(270);
			ugly.velocty.roundme();

			vector<int> closestUglys = this->getClosestUglysIdFrom(ugly);

			if (!ugly.velocty.isZero() && !closestUglys.empty())
			{
				EVector target(0, 0);
				for (auto &i : closestUglys)
					target += this->getFishById(i).pos;
				target /= closestUglys.size();
				EVector avoidDir = ugly.pos - target;
				if (!avoidDir.isZero())
				{
					avoidDir.setMag(200);
					ugly.velocty = avoidDir;
				}
			}
			this->updateUglySpeed(ugly);
			ugly.velocty.roundme();
		}
		else
		{
			EVector target(0, 0);
			for (auto &i : dronesId)
			{
				target += this->getDroneById(i).pos;
			}
			target /= dronesId.size();
			ugly.velocty = target - ugly.pos;
			ugly.velocty.limit(540);
			ugly.velocty.roundme();
		}
	}
}

