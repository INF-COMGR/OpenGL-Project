#include "barrel.h"

Barrel::Barrel(int size, QVector3D location) : size{size}, location{location}
{

}

int Barrel::getSize() {
    return this->size;
}

QVector3D Barrel::getLocation() {
    return this->location;
}

