#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <fstream>

#include "includes/Actions.hpp"
#include "includes/EVector.hpp"
#include "includes/Drone.hpp"
#include "includes/Fish.hpp"
#include "includes/Game.hpp"

/*start*/
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <utility>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <fstream>

using namespace std;

string	dn[] = {"B", "T", "R", "L", "BR", "TL", "TR", "BL"};
int		dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int		dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

pair<int, int> getDirection(string s)
{
	static map<string, pair<int, int> > dp;
	if (dp.count(s))
		return dp[s];
	pair<int, int> ans{-1, -1};
	for (int d = 0; d < 8; d++)
		if (dn[d] == s)
			return dp[s] = {dx[d], dy[d]};
	return dp[s] = ans;
}

double mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh)
{
	double fromRange = fromHigh - fromLow;
	double toRange = toHigh - toLow;
	double scaledValue = (value - fromLow) / fromRange;

	return toLow + (scaledValue * toRange);
}
