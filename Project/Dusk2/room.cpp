#include "room.h"

Room::Room(double x1, double y1, double z1, double x2, double y2, double z2) {
    this->wall1 = new Wall(x1, y1, z1, x2, y2, z1, DIRECTION::NORTH);
    this->wall2 = new Wall(x2, y1, z1, x2, y2, z2, DIRECTION::WEST);
    this->wall3 = new Wall(x2, y1, z2, x1, y2, z2, DIRECTION::SOUTH);
    this->wall4 = new Wall(x1, y1, z2, x1, y2, z1, DIRECTION::EAST);
    this->floor = new Floor(x1, z1, x2, z2);
}

Wall* Room::getWall1() {
    return this->wall1;
}

Wall* Room::getWall2() {
    return this->wall2;
}

Wall* Room::getWall3() {
    return this->wall3;
}

Wall* Room::getWall4() {
    return this->wall4;
}

Floor* Room::getFloor() {
    return this->floor;
}
