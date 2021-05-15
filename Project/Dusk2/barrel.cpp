#include "barrel.h"

Barrel::Barrel(int size, QVector3D location,  bool isFalling, float fallingSpeed):
    size{size}, location{location}, isFalling{isFalling}, fallingSpeed{fallingSpeed}
{}

int Barrel::getSize() {
    return this->size;
}

QVector3D Barrel::getLocation() {
    return this->location;
}

void Barrel::move() {
    if (location.y() <= 0)
        isFalling = false;
    else
        location.setY(location.y() - fallingSpeed);
}

void Barrel::setFalling() {
    isFalling = true;
}

bool Barrel::getFalling() {
    return isFalling;
}

