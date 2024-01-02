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
	/*header file*/
	"src/header.hpp",

	/*includes files*/
	"src/includes/EVector.hpp",
	"src/includes/SingleLinePath.hpp",
	"src/includes/Fish.hpp",
	"src/includes/Actions.hpp",
	"src/includes/Drone.hpp",
	"src/includes/Game.hpp",
	/*includes files*/

	/*Evector-Implm*/
	"src/classes/EVector.cpp",
	/*SingleLine-Impl*/
	"src/classes/SingleLinePath.cpp",

	/*Drone|Fish|Game|standart-Impl-File*/
	"src/classes/Drone.cpp",
	"src/classes/Fish.cpp",
	"src/classes/Game.cpp",
	"src/classes/Actions.cpp",
	/*Drone|Fish|Game|standart-Impl-File*/

	/*Game-Modules-Files*/

		/*game-setup*/
		"src/game-modules/game-setup/game_setup.cpp",
		"src/game-modules/game-setup/turn_setup.cpp",
		/*game-setup*/

		/*game-simulation*/
		"src/game-modules/game-simulation/fishes_simulation.cpp",
		"src/game-modules/game-simulation/uglys_simulation.cpp",

		/*game-utils-files*/
		"src/game-modules/game-utils/game_geters.cpp",
		/*game-utils-files*/

		/*game-debugs-file*/
		"src/game-modules/game-debugs/debugs.cpp",
		/*game-debugs-file*/
	/*Game-Modules-Files*/

	/*Drone-Work-Files*/
	"src/drone-work/drone_update.cpp",
	"src/drone-work/drone_avoidness.cpp",
	"src/drone-work/drone_light_evaluate.cpp",
	"src/drone-work/drone_kick_out_fish.cpp",
	"src/drone-work/drone_scan_fish.cpp",
	/*Drone-Work-Files*/


	/*solution|main|files*/
	"src/solutions/solution.cpp",
	"src/main.cpp"
	/*solution|main|files*/
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
