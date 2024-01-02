#include "header.hpp"
#include "../includes/Fish.hpp"

/*start*/

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

