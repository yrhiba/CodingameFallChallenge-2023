#include "../header.hpp"
#include "../includes/Drone.hpp"
#include "../includes/Fish.hpp"
#include "../includes/Game.hpp"
#include "../includes/Actions.hpp"

/*start*/

void Game::solution()
{
	Actions actions;

	// this->debug();
	cerr << "turn: " << this->game_turn << endl;

	for (auto &droneId : this->myDrones)
	{
		Drone &drone = this->getDroneById(droneId);
		EVector target(5e3, 5e3);

		EVector acc = target - drone.pos;
		acc.setMag(100);

		drone.velocty += acc;
		
		cerr << drone.velocty << " | " << drone.velocty.magnitude() << endl;

		drone.pos += drone.velocty;

		actions.moveToPos(drone.pos.x, drone.pos.y, 0);
	}

	return ;
}
