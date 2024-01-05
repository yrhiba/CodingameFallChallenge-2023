#include "../header.hpp"
#include "../A_includes/Drone.hpp"

/*start*/

void	Drone::initializeSetupGameData(void)
{
	this->id = 0;
	this->pos = EVector(0, 0);
	this->velocty = EVector(0, 0);
	this->acceleration = EVector(0, 0);
	this->TargetPos = EVector(0, 0);
	this->reachedTargetPos = false;
	this->emergency = 0;
	this->light = 0;
	this->battery = 0;
	this->isLightOn = false;
	this->myDrone = 0;
	this->opDrone = 0;
	this->maxForce = 1e9;
	this->maxSpeed = 600;
	this->wanderTheta = ((M_PI * -1) / 2);
	this->action = Actions();
	this->mission = 0;
	this->assignedFishToKick = false;
	this->TargetFishToKick = -1;
	this->assignedFishToScan = false;
	this->mustGoToTop = false;
	this->single_line_path = SingleLinePath();
}
