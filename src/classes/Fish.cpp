#include "../header.hpp"
#include "../includes/Fish.hpp"

/*start*/

Fish::Fish():
	id(-1), color(-1), type(-1), 
	x(-1), y(-1), prev_x(-1), prev_y(-1), 
	vx(-1), vy(-1), prev_vx(-1), prev_vy(-1),
	scaned(0), dead(0), 
	scannedByMe(0), scannedByOp(0),
	isVisible(0)
{
}

void Fish::setPos(int _x, int _y)
{
	this->x = _x;
	this->y = _y;
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
	os << " | Pos (" << fish.prev_x << "," << fish.prev_y << ") ->";
	os << " (" << fish.x << "," << fish.y << ") | ";
	os << " Speed (" << fish.prev_vx << "," << fish.prev_vy << ") -> ";
	os << " (" << fish.vx << "," << fish.vy << ")";
	return (os);
}
