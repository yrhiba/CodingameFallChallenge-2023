#pragma once

#include "../header.hpp"

/*start*/

struct Actions
{
	string message;

	Actions();

	void moveToPos(int _x, int _y, int _lighStat);
	void wait(int _lightStat);
	void setMsg(string _msg);
};
