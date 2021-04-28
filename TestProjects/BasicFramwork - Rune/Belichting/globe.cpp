#include "globe.h"

Globe::Globe(float radius, float red, float yellow, float blue)
{
    this->radius = radius;

    this->red = red;
    this->yellow = yellow;
    this->blue = blue;
}

float Globe::getRadius() {
    return this->radius;
}

float Globe::getRed() {
    return this->red;
}
float Globe::getYellow() {
    return this->yellow;
}
float Globe::getBlue() {
    return this->blue;
}
