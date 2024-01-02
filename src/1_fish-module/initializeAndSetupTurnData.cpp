#include "header.hpp"
#include "../includes/Fish.hpp"

/*start*/

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
