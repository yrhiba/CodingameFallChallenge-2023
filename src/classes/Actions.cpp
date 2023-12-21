#include "../includes/Actions.hpp"

/*start*/

void Actions::moveToPos(int _x, int _y, int _lighStat)
{
	cout << "MOVE " << _x << " " << _y << " " << _lighStat << endl;
}

void Actions::wait(int _lightStat)
{
	cout << "WAIT " << _lightStat << endl;
}
