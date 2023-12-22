// ########################
// file-Name: src/header.hpp
// ########################
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

// ########################
// file-Name: src/includes/EVector.hpp
// ########################

struct EVector
{
	double	x;
	double	y;

	EVector();
	EVector(double _x, double _y);
	EVector(const EVector &other);

	double	magnitude() const;
	void	normalize();
	void	setMag(double _magnitude);
	void	limit(double _magnitude);

	EVector &operator=(const EVector &vect);

	EVector operator+(const EVector &vect);
	EVector operator-(const EVector &vect);

	EVector &operator+=(const EVector &vect);
	EVector &operator-=(const EVector &vect);

	EVector &operator*=(int value);
	EVector &operator*=(double value);
};


istream &operator>>(istream &is, EVector &vect);
ostream &operator<<(ostream &os, const EVector &vect);

// ########################
// file-Name: src/includes/Drone.hpp
// ########################

struct Drone 
{
	int		id;
	EVector	pos;
	EVector	velocty;
	EVector	acceleration;
	int		battery;
	int		emergency;
	int		myDrone;
	int		opDrone;
	int		maxSpeed;
	int		light;

	string	direction;

	vector<int>					scannedCreatures;

	// creatureID : Direction
	vector<pair<int, string>>	creaturesDirection;

	// constructer
	Drone();

	bool operator<(const Drone &other) const;
	bool operator<=(const Drone &other) const;
	bool operator>(const Drone &other) const;
	bool operator>=(const Drone &other) const;
	bool operator==(const Drone &other) const;
};

istream &operator>>(istream &is, Drone &drone);
ostream &operator<<(ostream &os, const Drone &drone);

// ########################
// file-Name: src/includes/Fish.hpp
// ########################

struct Fish
{
	int		id;
	int		color;
	int		type;
	EVector	pos;
	EVector	prevPos;
	EVector velocty;
	EVector prevVelocty;
	int		scaned; // 0 : not-scanned || 1 : scanned
	int		dead;  // 0 : still alive || 1 : dead fish
	int		scannedByMe; // 0 | 1
	int		scannedByOp; // 0 | 1
	int		isVisible;  // 0 | 1

	/* TO DO: Simulate next move for this fish */
	/* 
		200 turn each turn we need to know each fish in wich postion
		gonna be !?;
	*/
	vector< int > simulate_next_pos_x; // TO DO
	vector< int > simulate_next_pos_y; // TO DO

	/* store distances between this fish and other drones  */
	// first: distance^2 | second: DroneId
	vector< pair<int, int> > fishDronePowerDistance;

	Fish();

	void setPos(EVector _pos);

	bool operator<(const Fish &other) const;
	bool operator<=(const Fish &other) const;
	bool operator>(const Fish &other) const;
	bool operator>=(const Fish &other) const;
	bool operator==(const Fish &other) const;
};

istream &operator>>(istream &is, Fish &fish);
ostream &operator<<(ostream &os, const Fish &fish);

// ########################
// file-Name: src/includes/Game.hpp
// ########################

struct Game
{
	// Total creatures in the Map
	int	game_turn;

	int	creature_count;
	int	creature_visible_count;
	int	fishes_visible_count;
	int	uglys_visible_count;

	int	my_score;
	int	my_scan_count;
	int	my_drone_count;

	int	op_score;
	int	op_scan_count;
	int	op_drone_count;

	// Fishes Informations
	vector<Fish>				allFishes;
	map<int, vector<int>>		typeFishes;
	map<int, bool>				isScannedFish;
	map<int, bool>				isScannedByMeFish;
	map<int, bool>				isScannedByOpFish;
	map<int, bool>				isDeadFish;

	// Drone Informations
	vector<Drone>				allDrones;
	vector<int>					myDrones;
	vector<int>					opponentsDrones;

	Game();

	void initTurn( void );

	// member function utilitys
	void readCreatures( void );
	void readScores( void );
	void readScannedCreatures( void );
	void readDrones( void );
	void readDronesCurrentScan( void );
	void readVisibleCreatures( void );
	void readRadarInfo( void );

	Fish &getFishById(int fishId);
	Drone &getDroneById(int droneId);


	void debug();
	void solution();
};

// ########################
// file-Name: src/includes/Actions.hpp
// ########################

struct Actions
{
	void moveToPos(int _x, int _y, int _lighStat);
	void wait(int _lightStat);
};

// ########################
// file-Name: src/classes/Drone.cpp
// ########################

Drone::Drone()
{
	this->light = 0;
	this->velocty = EVector(0, 0);
	this->acceleration = EVector(0, 0);
	this->maxSpeed = 600;
	this->direction = ((rand()%1) ? "BL" : "BR");
}

/* Drone Comparison Operators OverLoads */
bool Drone::operator<(const Drone &other) const
{
	return (this->id < other.id);
}

bool Drone::operator<=(const Drone &other) const
{
	return (this->id <= other.id);
}

bool Drone::operator>(const Drone &other) const
{
	return (this->id > other.id);
}

bool Drone::operator>=(const Drone &other) const
{
	return (this->id >= other.id);
}

bool Drone::operator==(const Drone &other) const
{
	return (this->id == other.id);
}


istream &operator>>(istream &is, Drone &drone)
{
	is >> drone.id >> drone.pos >> drone.emergency >> drone.battery;
	cin.ignore();
	return (is);
}

ostream &operator<<(ostream &os, const Drone &drone)
{
	os << "DroneId: " << drone.id;
	os << " | Battery: " << drone.battery;
	os << " | Emergency: " << drone.emergency;
	os << " | MyDrone: " << drone.myDrone;
	os << " | OpDrone: " << drone.opDrone;
	os << " | " << drone.pos;
	os << " | ScannedCreaturesIDs: ";
	for (auto &id : drone.scannedCreatures)
		os << id << " ";
	// os << " | Direction: " << drone.direction;
	return (os);
}

// ########################
// file-Name: src/classes/EVector.cpp
// ########################

EVector::EVector()
: x(0), y(0)
{
}

EVector::EVector(double _x, double _y)
	: x(_x), y(_y)
{
}

EVector::EVector(const EVector &other)
: x(other.x), y(other.y)
{
}

double EVector::magnitude() const
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}

void	EVector::normalize()
{
	double mag = this->magnitude();

	this->x /= mag;
	this->y /= mag;
}

void	EVector::setMag(double _magnitude)
{
	this->normalize();
	(*this) *= _magnitude;
}

void	EVector::limit(double _magnitude)
{
	if (this->magnitude() > _magnitude)
	{
		this->setMag(_magnitude);
	}
}

EVector &EVector::operator=(const EVector &vect)
{
	this->x = vect.x;
	this->y = vect.y;
	return (*this);
}

EVector EVector::operator+(const EVector &vect)
{
	return EVector(this->x + vect.x, this->y + vect.y);
}

EVector EVector::operator-(const EVector &vect)
{
	return EVector(this->x - vect.x, this->y - vect.y);
}

EVector &EVector::operator+=(const EVector &vect)
{
	this->x += vect.x;
	this->y += vect.y;
	return (*this);
}

EVector &EVector::operator-=(const EVector &vect)
{
	this->x -= vect.x;
	this->y -= vect.y;
	return (*this);
}

EVector &EVector::operator*=(double value)
{
	this->x *= value;
	this->y *= value;
	return (*this);
}

EVector &EVector::operator*=(int value)
{
	this->x *= value;
	this->y *= value;
	return (*this);
}

istream &operator>>(istream &is, EVector &vect)
{
	is >> vect.x >> vect.y;
	return is;
}

ostream &operator<<(ostream &os, const EVector &vect)
{
	os << "(" << vect.x << "," << vect.y << ")";
	return (os);
}

// ########################
// file-Name: src/classes/Fish.cpp
// ########################

Fish::Fish():
	id(-1), color(-1), type(-1), 
	pos(-1, -1), prevPos(-1, -1),
	velocty(-1, -1), prevVelocty(-1, -1),
	scaned(0), dead(0), 
	scannedByMe(0), scannedByOp(0),
	isVisible(0)
{
}

void Fish::setPos(EVector _pos)
{
	this->pos = _pos;
}

/* Fish Comparison Operators OverLoads */
bool Fish::operator<(const Fish &other) const
{
	return (this->id < other.id);
}

bool Fish::operator<=(const Fish &other) const
{
	return (this->id <= other.id);
}

bool Fish::operator>(const Fish &other) const
{
	return (this->id > other.id);
}

bool Fish::operator>=(const Fish &other) const
{
	return (this->id >= other.id);
}

bool Fish::operator==(const Fish &other) const
{
	return (this->id == other.id);
}

/* Fish read and write operators overloed */
istream &operator>>(istream &is, Fish &fish)
{
	is >> fish.id >> fish.color >> fish.type;
	return (is);
}

ostream &operator<<(ostream &os, const Fish &fish)
{
	os << "Id: " << fish.id << " | Color: " << fish.color;
	os << " | Type: " << fish.type << " | ScannedByMe: " << fish.scannedByMe;
	os << " | ScannedByOp: " << fish.scannedByOp;
	os << " | Pos " << fish.prevPos  << " ->";
	os << " " << fish.pos << " | ";
	os << " Speed " << fish.prevVelocty << " -> " << fish.velocty;
	return (os);
}

// ########################
// file-Name: src/classes/Game.cpp
// ########################

Game::Game()
:game_turn(-1)
{
}

void Game::readCreatures( void )
{
	cin >> this->creature_count;
	this->allFishes.resize(this->creature_count);
	for (auto &fish : this->allFishes)
	{
		cin >> fish; cin.ignore();
		this->typeFishes[fish.type].push_back(fish.id);
	}
	sort(this->allFishes.begin(), this->allFishes.end());
}

void Game::initTurn( void )
{
	this->isScannedFish.clear();
	this->isScannedByMeFish.clear();
	this->isScannedByOpFish.clear();
	this->isDeadFish.clear();

	this->creature_visible_count = 0;
	this->fishes_visible_count = 0;
	this->uglys_visible_count = 0;

	this->game_turn += 1;
}

void Game::readScores( void )
{
	cin >> this->my_score >> this->op_score;
	cin.ignore();
}

void Game::readScannedCreatures( void )
{
	/* What Me I Scan */
	cin >> this->my_scan_count; cin.ignore();
	for (int i = 0; i < this->my_scan_count; i++)
	{
		int creature_id;
		cin >> creature_id; cin.ignore();

		Fish &fish = this->getFishById(creature_id);

		this->isScannedByMeFish[fish.id] = true;
		this->isScannedFish[fish.id] = true;
		fish.scannedByMe = true;
		fish.scaned = true;
	}

	/* What Oponnents Scan */
	cin >> this->op_scan_count; cin.ignore();
	for (int i = 0; i < this->op_scan_count; i++)
	{
		int creature_id;
		cin >> creature_id; cin.ignore();

		Fish &fish = this->getFishById(creature_id);
		fish.scaned = true;
		fish.scannedByOp = true;
		this->isScannedByOpFish[creature_id] = true;
		this->isScannedFish[creature_id] = true;
	}
}

void Game::readDrones( void )
{
	if (this->game_turn)
	{
		// My Drones Status
		cin >> this->my_drone_count; cin.ignore();
		for (int i = 0; i < this->my_drone_count; i++)
		{
			Drone drone; cin >> drone;

			Drone &rDrone = this->getDroneById(drone.id);
			
			rDrone.pos = drone.pos;
			rDrone.emergency = drone.emergency;
			rDrone.battery = drone.battery;
			rDrone.scannedCreatures.clear();
			rDrone.creaturesDirection.clear();
		}

		// Oponents Drones Status
		cin >> this->op_drone_count; cin.ignore();
		for (int i = 0; i < this->op_drone_count; i++)
		{
			Drone drone; cin >> drone;
			
			Drone &rDrone = this->getDroneById(drone.id);
			
			rDrone.pos = drone.pos;
			rDrone.emergency = drone.emergency;
			rDrone.battery = drone.battery;
			rDrone.scannedCreatures.clear();
			rDrone.creaturesDirection.clear();
		}
	}
	else
	{
		// My Drones Status
		cin >> this->my_drone_count; cin.ignore();
		for (int i = 0; i < this->my_drone_count; i++)
		{
			Drone drone; cin >> drone;
			drone.myDrone = 1;
			drone.opDrone = 0;
			this->allDrones.push_back(drone);
			this->myDrones.push_back(drone.id);
		}

		// Oponents Drones Status
		cin >> this->op_drone_count; cin.ignore();
		for (int i = 0; i < this->op_drone_count; i++)
		{
			Drone drone; cin >> drone;
			drone.myDrone = 0;
			drone.opDrone = 1;
			this->allDrones.push_back(drone);
			this->opponentsDrones.push_back(drone.id);
		}

		sort(this->allDrones.begin(), this->allDrones.end());
	}
}

void Game::readDronesCurrentScan( void )
{
	int drone_scan_count;
	cin >> drone_scan_count; cin.ignore();
	for (int i = 0; i < drone_scan_count; i++)
	{
		int drone_id;
		int creature_id;
		cin >> drone_id >> creature_id; cin.ignore();

		Drone &drone = this->getDroneById(drone_id);
		drone.scannedCreatures.push_back(creature_id);
	}
}

void Game::readVisibleCreatures( void )
{
	/* Creatures (fishes) positions */
	cin >> this->creature_visible_count; cin.ignore();
	for (int i = 0; i < this->creature_visible_count; i++)
	{
		int creature_id, creature_x, creature_y, creature_vx, creature_vy;
		cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();

		Fish &fish = this->getFishById(creature_id);

		fish.isVisible = true;

		fish.prevPos = fish.pos;

		fish.pos = EVector(creature_x, creature_y);

		fish.prevVelocty = fish.velocty;

		fish.velocty = EVector(creature_vx, creature_vy);

		this->fishes_visible_count += (fish.type >= 0);
		this->uglys_visible_count += (fish.type == -1);
	}
}

void Game::readRadarInfo( void )
{
	int radar_blip_count; cin >> radar_blip_count; cin.ignore();
	for (int i = 0; i < radar_blip_count; i++)
	{
		int drone_id, creature_id; string radar;
		cin >> drone_id >> creature_id >> radar; cin.ignore();

		Drone &drone = this->getDroneById(drone_id);
		drone.creaturesDirection.push_back({creature_id, radar});
	}
}

void Game::debug( void )
{
	cerr << "Turn: " << this->game_turn << endl;
	cerr << "Creaturs-Count: " << this->creature_count << endl;
	cerr << "MyScore: " << this->my_score << " | OpScore: " << this->op_score << endl;
	cerr << "MyDroneCount: " << this->my_drone_count << " | OpDroneCount: " << this->op_drone_count << endl;
	cerr << "MyScanCount: " << this->my_scan_count << " | OpScanCount: " << this->op_scan_count << endl;  
	cerr << endl;

	cerr << "Fishes Informations: " << endl;
	for (auto &fish : this->allFishes)
		cerr << fish << endl;
	cerr << endl;

	cerr << "Drones Informations: " << endl;
	for (auto &drone : this->allDrones)
	{
		cerr << drone << endl;
		cerr << "Drone Creatures Radar: " << endl;
		for (auto &[creatureID, direction] : drone.creaturesDirection)
			cerr << creatureID << "," << direction << " | ";
		cerr << endl << endl;
	}
}

Fish &Game::getFishById(int fishId)
{
	int start = 0;
	int end = this->allFishes.size() - 1;
	int mid, ans = -1;

	while (start <= end)
	{
		mid = start + ((end - start) / 2);

		if (this->allFishes[mid].id == fishId)
			return this->allFishes[mid];

		if (this->allFishes[mid].id < fishId)
		{
			start = mid + 1;   
		}
		else
		{
			end = mid - 1;
		}
	}

	return this->allFishes.back();
}

Drone &Game::getDroneById(int droneId)
{
	int start = 0;
	int end = this->allDrones.size() - 1;
	int mid, ans = -1;

	while (start <= end)
	{
		mid = start + ((end - start) / 2);

		if (this->allDrones[mid].id == droneId)
			return this->allDrones[mid];

		if (this->allFishes[mid].id < droneId)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
	}

	return this->allDrones.back();
}


// ########################
// file-Name: src/classes/Actions.cpp
// ########################

void Actions::moveToPos(int _x, int _y, int _lighStat)
{
	cout << "MOVE " << _x << " " << _y << " " << _lighStat << endl;
}

void Actions::wait(int _lightStat)
{
	cout << "WAIT " << _lightStat << endl;
}

// ########################
// file-Name: src/solutions/solution.cpp
// ########################

void Game::solution()
{

	cerr << "Visible Creatures: " << this->creature_visible_count << endl;
	cerr << "Visible Fishes: " << this->fishes_visible_count << endl;
	cerr << "Visible Uglys: " << this->uglys_visible_count << endl;

	/*
		PART ZERO:
			- calculate all the visible fishes and uglys for all my drones.
			- calculate the scores (saved and unsaved)
			- mark the danger drones.
			- decide the priorityes PART to be consider first.
	*/

	Actions actions;

	// this->debug();

	for (auto &droneId : this->myDrones)
	{
		Drone &curDrone = this->getDroneById(droneId);

		/*
			- mark the visible creatures

			- count the visible fishes | the visible Uglys

			- count the scanned fishes | score and accordine to the global current score gained + current score not saved Yet.

			- see possiblitys of begin the first ho save something

			// PARSING PART : Construct the Information Needed Later.

			// Pre Algo : Use Some Probabilty TO decide predicted best choice (ligh, wait) etc.

			// PART ONE : Calculate the Best MOVE POSITION

			if (countVisible == 0)
			{
				// EXPLORE MORE
			}
			else if (countVisibleUGLY > 0)
			{
				// Flee From them
			}
			else if (countVisibleFishes > 0)
			{
				// DO something with not Saved Yet

				// DO something with already Saved Fishes
			}

			// PART TWO : use some information from the part one to decide if i want to use light or not?

			if (something)
			{
				// light on
			}
			else
			{
				// light off
			}

			FINAL PART: Use all decided action need to be do, and choice the priorityz one!
		*/

		/* add to actions the final descion */
		// actions.moveToPos(curDrone.pos.x, curDrone.pos.y, curDrone.light);
		actions.wait(curDrone.light);
	}

	return ;
}

// ########################
// file-Name: src/main.cpp
// ########################

int main()
{
	/* Initialize Random Generation */
	srand(time(NULL));

	/* intialize the game */
	Game game;

	/* read Creatures */
	game.readCreatures();

	/* Game Loop */
	while (true) 
	{
		/* Initialize Data */
		game.initTurn();

		/* Read Scores */
		game.readScores();

		/* Read Scanned Creatures (Me, Opponets) */
		game.readScannedCreatures();

		/* Read My Drones and Opponnets Drones */
		game.readDrones();

		/* Read Drones current creatures scann */ 
		game.readDronesCurrentScan();

		/* Creatures(fishes) Position */
		game.readVisibleCreatures();

		/* Read Creatures Radar Direction */
		game.readRadarInfo();

		/* puts the solution */
		game.solution();
	}

	return (0);
}

