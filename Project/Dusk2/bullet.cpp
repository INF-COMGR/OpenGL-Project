#include "bullet.h"

Bullet::Bullet(QVector3D location, QVector3D flyingDirection):
    location{location}, flyingDirection{flyingDirection}
{
    this->location.setY(this->location.y()-0.3);
}

void Bullet::move() {
    location.setX(location.x()+flyingDirection.x());
    location.setY(location.y()+flyingDirection.y());
    location.setZ(location.z()+flyingDirection.z());
}

QVector3D Bullet::getLocation() {
    return location;
}
