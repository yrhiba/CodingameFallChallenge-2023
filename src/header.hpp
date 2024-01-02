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

#include "includes/SingleLinePath.hpp"
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

# define MAP_SIZE 10000

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

# define DEBUG 0

double mapValue(double value, double fromLow, double fromHigh, double toLow, double toHigh)
{
	double fromRange = fromHigh - fromLow;
	double toRange = toHigh - toLow;
	double scaledValue = (value - fromLow) / fromRange;

	return toLow + (scaledValue * toRange);
}

pair<EVector, EVector> calcTheIntersctionReactangle(vector<pair<EVector, EVector>> &rectangles)
{
	if (rectangles.empty())
	{
		cerr << "No-information-for-that-fish." << endl;
		return {EVector(0, 0), EVector(9999, 9999)};
	}

	double maxLeft = rectangles[0].first.x;
	double maxTop = rectangles[0].first.y;
	double minRight = rectangles[0].second.x;
	double minBottom = rectangles[0].second.y;

	// Iterate through the rectangles to find the intersection
	for (const auto &rect : rectangles)
	{
		maxLeft = max(maxLeft, rect.first.x);
		maxTop = max(maxTop, rect.first.y);
		minRight = min(minRight, rect.second.x);
		minBottom = min(minBottom, rect.second.y);
	}

	// Check if there is a valid intersection
	if (maxLeft < minRight && maxTop < minBottom)
	{
		// Return the intersection rectangle
		return {EVector(maxLeft, maxTop), EVector(minRight, minBottom)};
	}
	else
	{
		cerr << "there-is-something-wrong-with-radar." << endl;
		return {EVector(0, 0), EVector(9999, 9999)};
	}
}
