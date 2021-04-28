#include "room.h"

Room::Room(float width, float length) {
    this->length = length;
    this->width = width;
}

float Room::getLength() {
    return this->length;
}

float Room::getWidth() {
    return this->width;
}
