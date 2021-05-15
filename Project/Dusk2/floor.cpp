#include "floor.h"

Floor::Floor(double x1, double z1, double x2, double z2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->z1 = z1;
    this->z2 = z2;
}

QVector3D* Floor::getBottomLeft() {
    return new QVector3D(x1, 0, z1);
}
QVector3D* Floor::getBottomRight() {
    return new QVector3D(x2, 0, z1);
}
QVector3D* Floor::getTopLeft() {
    return new QVector3D(x1, 0, z2);
}
QVector3D* Floor::getTopRight() {
    return new QVector3D(x2, 0, z2);
}
