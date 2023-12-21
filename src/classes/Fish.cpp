

/*start*/

struct Fish
{
    int id;
    int color;
    int type;
    int x;
    int y;
    int prev_x; // previous x position
    int prev_y; // previous y position
    int vx; // speed direction x-axis 
    int vy; // speed direction y-axis
    int prev_vx;
    int prev_vy;
    int scaned; // 0 : not-scanned || 1 : scanned
    int dead;  // 0 : still alive || 1 : dead fish
    int scannedByMe; // 0 | 1
    int scannedByOp; // 0 | 1
    int isVisible;  // 0 | 1

    /* TO DO: Simulate next move for this fish */
    /* 
        200 turn each turn we need to know each fish in wich postion
        gonna be !?;
    */
    vector< int > simulate_next_pos_x; // TO DO
    vector< int > simulate_next_pos_y; // TO DO

    /* store distances between this fish and other drones  */
    vector< pair<int, int> > fishDronePowerDistance; // first: distance^2 | second: DroneId

    Fish() : id(-1), color(-1), type(-1), x(-1), y(-1), prev_x(-1), prev_y(-1), 
    vx(-1), vy(-1), prev_vx(-1), prev_vy(-1),
    scaned(0), dead(0), scannedByMe(0), scannedByOp(0), isVisible(0)
    {
    }

    void setPos(int _x, int _y)
    {
        this->x = _x;
        this->y = _y;
    }

    /* Fish Comparison Operators OverLoads */
    bool operator<(const Fish &other) const
    {
        return (this->id < other.id);
    }
    bool operator<=(const Fish &other) const
    {
        return (this->id <= other.id);
    }
    bool operator>(const Fish &other) const
    {
        return (this->id > other.id);
    }
    bool operator>=(const Fish &other) const
    {
        return (this->id >= other.id);
    }
    bool operator==(const Fish &other) const
    {
        return (this->id == other.id);
    }
};

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