#include "barrel.h"
#include "hitbox.h"

Barrel::Barrel(int size, QVector3D location,  bool isFalling, float fallingSpeed):
    size{size}, location{location}, isFalling{isFalling}, fallingSpeed{fallingSpeed}
{
    this->sideSize = size/1.5f;
    this->hitbox = new HitBox(QVector3D(location.x()-sideSize, location.y()+size, location.z()-sideSize),
                              QVector3D(location.x()+sideSize, location.y(), location.z()+sideSize));
}

int Barrel::getSize() {
    return this->size;
}

QVector3D Barrel::getLocation() {
    return this->location;
}

void Barrel::move() {
    if (location.y() > 0 && !hasCollided()) {
        location.setY(location.y() - fallingSpeed);
        hitbox->update(QVector3D(location.x()-sideSize, location.y()+size, location.z()-sideSize),
                       QVector3D(location.x()+sideSize, location.y(), location.z()+sideSize));
    }
}

bool Barrel::hasCollided() {
    for (int i = 0; i < otherHitBoxes.length(); ++i) {
        if (otherHitBoxes[i]->isHitBoxInside(*hitbox))
            return true;
    }
    return false;
}

void Barrel::setFalling() {
    isFalling = true;
}

bool Barrel::getFalling() {
    return isFalling;
}

HitBox* Barrel::getHitBox() {
    return this->hitbox;
}

QVector<HitBox*> Barrel::getHitBoxes() {
    return this->otherHitBoxes;
}

void Barrel::addHitBox(HitBox* hitbox) {
    this->otherHitBoxes.append(hitbox);
}

