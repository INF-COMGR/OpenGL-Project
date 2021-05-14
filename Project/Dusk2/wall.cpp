#include "wall.h"

Wall::Wall(double x1, double y1, double z1, double x2, double y2, double z2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->z1 = z1;
    this->x2 = x2;
    this->y2 = y2;
    this->z2 = z2;
}

QVector<double>* Wall::getBottomLeft() {
    return new QVector<double>({x1, y1, z1});
}
QVector<double>* Wall::getBottomRight() {
    return new QVector<double>({x2, y1, z2});
}
QVector<double>* Wall::getTopLeft() {
    return new QVector<double>({x1, y2, z1});
}
QVector<double>* Wall::getTopRight() {
    return new QVector<double>({x2, y2, z2});
}
