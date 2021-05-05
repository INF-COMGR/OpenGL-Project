#include "floor.h"

Floor::Floor(double x1, double z1, double x2, double z2)
{
    this->x1 = x1;
    this->x2 = x2;
    this->z1 = z1;
    this->z2 = z2;
}

QVector<double>* Floor::getBottomLeft() {
    return new QVector<double>({x1, 0, z1});
}
QVector<double>* Floor::getBottomRight() {
    return new QVector<double>({x2, 0, z1});
}
QVector<double>* Floor::getTopLeft() {
    return new QVector<double>({x1, 0, z2});
}
QVector<double>* Floor::getTopRight() {
    return new QVector<double>({x2, 0, z2});
}
