#ifndef ROOM_H
#define ROOM_H
#include "wall.h"
#include "floor.h"

class Room
{
public:
    Room(double x1, double y1, double z1, double x2, double y2, double z2);
    Wall* getWall1();
    Wall* getWall2();
    Wall* getWall3();
    Wall* getWall4();
    Floor* getFloor();

private:
    Wall* wall1;
    Wall* wall2;
    Wall* wall3;
    Wall* wall4;
    Floor* floor;
};

#endif // ROOM_H
