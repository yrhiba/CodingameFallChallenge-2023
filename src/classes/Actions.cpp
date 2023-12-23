#include "../includes/Actions.hpp"

/*start*/

Actions::Actions() : message(".Y.R.")
{
}

void Actions::moveToPos(int _x, int _y, int _lighStat)
{
	cout << "MOVE " << _x << " " << _y << " " << _lighStat;
	cout << " " << this->message << endl;
}

void Actions::wait(int _lightStat)
{
	cout << "WAIT " << _lightStat << " " << this->message << endl;
}

void Actions::setMsg(string _msg)
{
	this->message = _msg;
}
