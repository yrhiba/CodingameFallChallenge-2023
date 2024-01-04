#include "header.hpp"
#include "Drone.hpp"

/*start*/

void	Drone::initializeAndSetupTurnData(void)
{
	this->velocty = EVector(0, 0);
	this->acceleration = EVector(0, 0);
	this->scannedCreatures.clear();
	this->light = 0;
	this->action = Actions();

	this->priorityzeFishesToScan.clear();
	this->rightDrone = false;
	this->leftDrone = false;

	/*data-related-to-update-drone*/
	// this->mission = 0;
	// this->TargetPos = EVector(0, 0);
	// this->assignedFishToScan = false;
	// this->TargetFishToScan = -1;
	// this->assignedFishToKick = false;
	// this->TargetFishToKick = -1;
	// this->mustGoToTop = false;
	/*data-related-to-update-drone*/
}
