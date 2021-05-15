#include "bullet.h"
#include "hitbox.h"

Bullet::Bullet(QVector3D location, QVector3D flyingDirection):
    location{location}, flyingDirection{flyingDirection}
{
    this->location.setY(this->location.y()-0.3);
    this->hitboxes = QVector<HitBox*>();
}

bool Bullet::getCollided() {
    return isCollided;
}

void Bullet::update() {
    if (hasCollided()) {
        isCollided = true;
    } else {
        move();
    }
}

void Bullet::move() {
    location.setX(location.x()+flyingDirection.x());
    location.setY(location.y()+flyingDirection.y());
    location.setZ(location.z()+flyingDirection.z());
}

QVector3D Bullet::getLocation() {
    return location;
}

void Bullet::addHitBox(HitBox* hitbox) {
    hitboxes.append(hitbox);
}

bool Bullet::hasCollided() {
    for (int i = 0; i < hitboxes.length(); ++i) {
        if (hitboxes[i]->isPointInside(location))
            return true;
    }
    return false;
}
