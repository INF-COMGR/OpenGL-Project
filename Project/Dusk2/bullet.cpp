#include "bullet.h"
#include "hitbox.h"

Bullet::Bullet(QVector3D location, QVector3D flyingDirection, QVector3D fallingDirection, bool isBullet):
    location{location}, flyingDirection{flyingDirection}, fallingDirection{fallingDirection}, isBullet{isBullet}
{
    this->location.setY(this->location.y()-0.3);
    this->hitboxes = QVector<HitBox*>();
    isCollided = false;
}

bool Bullet::getCollided() {
    return isCollided;
}

void Bullet::update() {
    if (!hasCollided())
        move();

}

void Bullet::move() {
    if (!isCollided && location.y() > 0) {
        flyingDirection.setX(flyingDirection.x()+fallingDirection.x());
        flyingDirection.setY(flyingDirection.y()+fallingDirection.y());
        flyingDirection.setZ(flyingDirection.z()+fallingDirection.z());

        location.setX(location.x()+flyingDirection.x());
        location.setY(location.y()+flyingDirection.y());
        location.setZ(location.z()+flyingDirection.z());
    }
}

bool Bullet::getIsBullet() const
{
    return isBullet;
}

QVector3D Bullet::getLocation() {
    return location;
}

void Bullet::addHitBox(HitBox* hitbox) {
    hitboxes.append(hitbox);
}

bool Bullet::hasCollided() {
    for (int i = 0; i < hitboxes.length(); ++i) {
        if (hitboxes[i]->isPointInside(location)) {
            if (isBullet)
                hitboxes[i]->setHitByBullet();
            return true;
        }
    }
    return false;
}
