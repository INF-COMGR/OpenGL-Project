#include "hitbox.h"

HitBox::HitBox(QVector3D topLeft, QVector3D bottomRight):
    topleftCorner{topLeft}, bottomRightCorner{bottomRight}
{}


bool HitBox::isPointInside(QVector3D point) {
    if (isInvalid)
        return false;
    else
    return (point.x() >= topleftCorner.x() && point.x() <= bottomRightCorner.x()) &&
           (point.y() >= bottomRightCorner.y() && point.y() <= topleftCorner.y()) &&
           (point.z() >= topleftCorner.z() && point.z() <= bottomRightCorner.z());
}

bool HitBox::isHitBoxInside(HitBox box) {
    QVector3D otherTopLeftConer = box.getTopLeft();
    QVector3D otherBottomRightCorner = box.getBottomRight();
    if (isInvalid)
        return false;
    else
    return (otherTopLeftConer.x() <= bottomRightCorner.x() && otherBottomRightCorner.x() >= topleftCorner.x()) &&
           (otherBottomRightCorner.y() <= topleftCorner.y() && otherTopLeftConer.y() >= bottomRightCorner.y()) &&
           (otherTopLeftConer.z() <= bottomRightCorner.z() && otherBottomRightCorner.z() >= topleftCorner.z());
}

QVector3D HitBox::getTopLeft() {
    return topleftCorner;
}

QVector3D HitBox::getBottomRight() {
    return bottomRightCorner;
}

void HitBox::update(QVector3D topleft, QVector3D bottomRight) {
    this->topleftCorner = topleft;
    this->bottomRightCorner = bottomRight;
}

void HitBox::setHitByBullet() {
    this->wasHitByBullet = true;
}

bool HitBox::getHitByBullet() {
    return this->wasHitByBullet;
}

void HitBox::setInvalid() {
    isInvalid = true;
}
