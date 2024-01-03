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

void	Game::uglysSimulation(void)
{
	vector<int> &allUglys = this->typeFishes[-1];
	for (int UglyId : allUglys)
	{
		Fish &ugly = this->getFishById(UglyId);
		if ((ugly.visibleAtTurn == -1) || (ugly.visibleAtTurn == this->game_turn)) continue;
		ugly.velocty.roundme();
		ugly.pos += ugly.velocty;
		this->snapUglyToZone(ugly.pos);
	}
	for (int UglyId : allUglys)
	{
		Fish &ugly = this->getFishById(UglyId);
		if ((ugly.visibleAtTurn == -1) || (ugly.visibleAtTurn == this->game_turn)) continue;
		vector<int> dronesId = this->getDronesTargetForUgly(ugly);
		if (!dronesId.empty())
		{
			EVector target(0, 0);
			for (int &droneID : dronesId)
				target += this->getDroneById(droneID).pos;
			target /= dronesId.size();
			ugly.velocty = target - ugly.pos;
			ugly.velocty.limit(540);
			ugly.velocty.roundme();
		}
		else
		{
			ugly.velocty.limit(270);
			ugly.velocty.roundme();
			vector<int> closestUglys = this->getClosestUglysIdFrom(ugly);
			if (!ugly.velocty.isZero() && !closestUglys.empty())
			{
				EVector target(0, 0);
				for (int &uglyID : closestUglys)
					target += this->getFishById(uglyID).pos;
				target /= closestUglys.size();
				EVector avoidDir = ugly.pos - target;
				if (!avoidDir.isZero())
				{
					avoidDir.setMag(200);
					avoidDir.roundme();
					ugly.velocty = avoidDir;
				}
			}
			EVector nextPos = ugly.pos + ugly.velocty;
			if ((nextPos.x < 0 && nextPos.x < ugly.pos.x) || 
				(nextPos.x > 9999 && nextPos.x > ugly.pos.x))
			{
				ugly.velocty.x *= -1;
			}
			if ((nextPos.y < 2500 && nextPos.y < ugly.pos.y) || 
				(nextPos.y > 9999 && nextPos.y > ugly.pos.y))
			{
				ugly.velocty.y *= -1;
			}
			ugly.velocty.roundme();
		}
	}
}
