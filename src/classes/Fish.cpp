#include "../header.hpp"
#include "../includes/Fish.hpp"

/*start*/

Fish::Fish():
	id(-1), color(-1), type(-1), 
	pos(-1, -1), nextSimulatedPos(-1, -1),
	velocty(-1, -1), nextSimulatedVel(-1, -1),
	scaned(0), dead(0), 
	scannedByMe(0), scannedByOp(0),
	isVisible(0), visibleAtTurn(-1)
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
	os << " | Pos " << fish.pos << " | ";
	os << " Speed " << fish.velocty;
	return (os);
}
