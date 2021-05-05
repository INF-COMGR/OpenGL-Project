#include "room.h"

Room::Room(double x1, double y1, double z1, double x2, double y2, double z2) {
    this->wall1 = new Wall(x1, y1, z1, x2, y2, z1);
    this->wall2 = new Wall(x2, y1, z1, x2, y2, z2);
    this->wall3 = new Wall(x2, y1, z2, x1, y2, z2);
    this->wall4 = new Wall(x1, y1, z2, x1, y2, z1);

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
