#include "header.hpp"
#include "../includes/Fish.hpp"

/*start*/

bool	Fish::isDeadNextTurn(void)
{
	EVector nextPos = this->pos + this->velocty;

	if (nextPos.x < 0 || nextPos.x > 9999)
	{
		return true;
	}

	return false;
}

void	Fish::setNextPos(void)
{
	this->nextPos = this->pos + this->velocty;
	this->snapToZone();
}

void	Fish::setStandardFishZone(void)
{
	if (this->type == -1)
		this->existZones.push_back({EVector(0, 2500), EVector(9999, 9999)});
	else if (this->type == 0)
		this->existZones.push_back({EVector(0, 2500), EVector(9999, 5000)});
	else if (this->type == 1)
		this->existZones.push_back({EVector(0, 5000), EVector(9999, 7500)});
	else if (this->type == 2)
		this->existZones.push_back({EVector(0, 7500), EVector(9999, 9999)});
}

void	Fish::setAvaillabilty(void)
{
	if ((this->type == -1) || this->dead)
	{
		this->availableToKick = false;
		this->availlableToscan = false;
		return ;
	}

	if (this->scannedByMe || this->unsavedScanedByMe)
	{
		this->availlableToscan = false;
	}
	else
	{
		this->availlableToscan = true;
	}

	if (this->scannedByOp || this->unsavedScanedByOP)
	{
		this->availableToKick = false;
	}
	else
	{
		this->availableToKick = true;
	}
}

void	Fish::snapToZone(void)
{
	if (this->existZones.empty())
		return ;

	int minx, maxx;
	int miny, maxy;

	minx = this->existZones.front().first.x;
	miny = this->existZones.front().first.y;
	maxx = this->existZones.front().second.x;
	maxy = this->existZones.front().second.y;

	if (this->pos.x < minx)
		this->pos.x = minx;

	if (this->pos.x > maxx)
		this->pos.x = maxx;

	if (this->pos.y < miny)
		this->pos.y = miny;

	if (this->pos.y > maxy)
		this->pos.y = maxy;
}

void	Fish::pushExistZone(EVector pos, string radar)
{
	// push back the fish zone depending on direction given by radar
	if (radar == "TL")
	{
		this->existZones.push_back({EVector(0, 0), pos});
	}
	else if (radar == "TR")
	{
		this->existZones.push_back({EVector(pos.x, 0), EVector(9999, pos.y)});
	}
	else if (radar == "BR")
	{
		this->existZones.push_back({pos, EVector(9999, 9999)});
	}
	else if (radar == "BL")
	{
		this->existZones.push_back({EVector(0, pos.y), EVector(pos.x, 9999)});
	}
}

void	Fish::extimatePossiblePosition(void)
{
	if ((this->type != -1) && (this->dead || (this->existZones.size() != 3)))
	{
		this->dead = true;
		this->estimationPosition = EVector(-1, -1);
		return;
	}

	this->existZone = calcTheIntersctionReactangle(this->existZones);

	EVector vect = this->existZone.second - this->existZone.first;

	vect.setMag(calcDistance(this->existZone.first, this->existZone.second) / 2.0);

	vect.roundme();

	this->estimationPosition = this->existZone.first + vect;
}

void	Fish::initializeSetupGameData(void)
{
	this->id = 0;
	this->color = 0;
	this->type = 0;
	this->pos = EVector(0, 0);
	this->velocty = EVector(0, 0);
	this->nextPos = EVector(0, 0);
	this->scaned = false;
	this->dead = false;
	this->deadNextTurn = false;
	this->scannedByMe = false;
	this->scannedByOp = false;
	this->unsavedScanedByMe = false;
	this->unsavedScanedByOP = false;
	this->isVisible = false;
	this->visibleAtTurn = -1;
	this->availableToKick = true;
	this->availlableToscan = true;
	this->dronesScan = set<int>();
	this->myDronesScan = set<int>();
	this->opDronesScan = set<int>();
	this->existZone = make_pair(EVector(0, 0), EVector(1e4, 1e4));
	this->existZones = vector< pair<EVector, EVector> >();
	this->estimationPosition = EVector(0, 0);
}

void	Fish::initializeAndSetupTurnData(void)
{
	this->scaned = false;
	this->scannedByMe = false;
	this->scannedByOp = false;
	this->unsavedScanedByMe = false;
	this->unsavedScanedByOP = false;
	this->dronesScan = set<int>();
	this->myDronesScan = set<int>();
	this->opDronesScan = set<int>();
	this->existZone = make_pair(EVector(0, 0), EVector(1e4, 1e4));
	this->existZones = vector< pair<EVector, EVector> >();
	this->estimationPosition = EVector(0, 0);
	this->setStandardFishZone();
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
	os << " | Pos " << fish.pos << " | ";
	os << " Speed " << fish.velocty;
	return (os);
}
