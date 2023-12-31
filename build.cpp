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


vector<string> files =
{
	"src/header.hpp",

	"src/includes/EVector.hpp",

	"src/includes/SingleLinePath.hpp",

	"src/includes/Fish.hpp",

	"src/includes/Drone.hpp",

	"src/includes/Game.hpp",

	"src/classes/SingleLinePath.cpp",

	"src/includes/Actions.hpp",

	"src/classes/Drone.cpp",

	"src/classes/EVector.cpp",

	"src/classes/Fish.cpp",

	"src/classes/Game.cpp",

	"src/game-modules/fihes_targtet_point.cpp",

	"src/game-modules/ugly_simulation.cpp",

	"src/game-modules/drone_avoidness.cpp",

	"src/drone-work/drone_update.cpp",

	"src/drone-work/light_evaluate.cpp",

	"src/game-debugs/debugs.cpp",

	"src/classes/Actions.cpp",

	"src/solutions/solution.cpp",

	"src/main.cpp"
};


int main()
{
	ofstream out("./prod/code.cpp");

	for (auto &file : files)
	{
		ifstream	fin(file);
		string		content;

		while (content != "/*start*/")
			getline(fin, content);

		out << "// ########################" << endl;
		out << "// file-Name: " << file << endl;
		out << "// ########################" << endl;

		getline(fin, content, '\0');

		out << content << endl;
	}

	out.close();

	return (0);
}
