#include "wall.h"
#include "hitbox.h"
#include <QVector3D>

Wall::Wall(double x1, double y1, double z1, double x2, double y2, double z2, DIRECTION direction)
{
    this->x1 = x1;
    this->y1 = y1;
    this->z1 = z1;
    this->x2 = x2;
    this->y2 = y2;
    this->z2 = z2;

    const float offset = 100;
    switch (direction) {
    case (DIRECTION::NORTH):
        this->hitbox = new HitBox(QVector3D(x1, y2, z1-offset), QVector3D(x2, y1, z2));
        break;
    case (DIRECTION::WEST):
        this->hitbox = new HitBox(QVector3D(x1, y2, z1), QVector3D(x2+offset, y1, z2));
        break;
    case (DIRECTION::SOUTH):
        this->hitbox = new HitBox(QVector3D(x2, y2, z2), QVector3D(x1, y1, z1+offset));
        break;
    case (DIRECTION::EAST):
        this->hitbox = new HitBox(QVector3D(x2-offset, y2, z2), QVector3D(x1, y1, z1));
        break;
    }


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

HitBox* Wall::getHitBox() {
    return this->hitbox;
}
