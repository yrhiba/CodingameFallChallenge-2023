#pragma once

#include "../header.hpp"

/*start*/

struct Actions
{
	int			isWaiting;
	EVector		pos;
	int			light;
	string		message;
	set<int>	uglyToAvoid;

	Actions();

	void moveToPos(int _x, int _y, int _lighStat);
	void wait(int _lightStat);
	void setMsg(string _msg);
	void debug(int	droneId);
};
