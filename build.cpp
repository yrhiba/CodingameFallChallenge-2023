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
	"src/classes/Actions.cpp",
	/*Drone|Fish|Game|standart-Impl-File*/

	/*Game-Module-Files*/
		/*game-setup*/
		"src/game-module/0_game-setup/readSetupCreatures.cpp",
		"src/game-module/0_game-setup/readSetupDrones.cpp",
		/*game-setup*/

		/*game-turn-init*/
		"src/game-module/1_game-init-turn/initTurn.cpp",
		/*game-turn-init*/

		/*game-read-input*/
		"src/game-module/2_game-readinput/readTurnData.cpp",
		/*game-read-input*/

		/*game-updates-fishes-drone*/
		"src/game-module/3_game-updatefishesdrones/setFishesFlagsAndUpdates.cpp",
		"src/game-module/3_game-updatefishesdrones/setDronesFlagsAndUpdates.cpp",
		/*game-updates-fishes-drone*/

		/*game-simulation*/
		"src/game-module/4_game-simulation/fishesSimulation.cpp",
		"src/game-module/4_game-simulation/uglysSimulation.cpp",

		/*game-utils-files*/
		"src/game-module/A_game-utils/game_geters.cpp",
		/*game-utils-files*/

		/*game-debugs-file*/
		"src/game-module/B_game-debugs/debugs.cpp",
		/*game-debugs-file*/
	/*Game-Module-Files*/

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
