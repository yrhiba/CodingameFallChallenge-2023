#include "../includes/Actions.hpp"

/*start*/

Actions::Actions() : message(".Y.R.")
{
}

void Actions::moveToPos(int _x, int _y, int _lighStat)
{
	this->isWaiting = false;
	this->pos = EVector(_x, _y);
	this->light = _lighStat;
	cout << "MOVE " << _x << " " << _y << " " << _lighStat;
	cout << " " << this->message << endl;
}

void Actions::wait(int _lightStat)
{
	this->isWaiting = true;
	this->light = _lightStat;
	cout << "WAIT " << _lightStat << " " << this->message << endl;
}

void Actions::setMsg(string _msg)
{
	this->message = _msg;
}

void Actions::debug(int	droneId)
{
	cerr << "Drone: " << droneId << ", ";

	if (!(this->isWaiting))
	{
		cerr << "Move-Pos: " << this->pos << ", Light-State: " << (this->light?"on":"off") << endl;
	}
	else
	{
		cerr << "Is Waiting, Light-State: " << (this->light?"on":"off") << endl;
	}
}
