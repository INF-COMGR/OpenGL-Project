#ifndef BARREL_H
#define BARREL_H

#include "QVector"
#include "QVector3D"
class HitBox;

class Barrel
{
public:
    enum BARRELTYPE { NORMAL, FIREBARREL, EXPLOSIVE };
    Barrel(int size, QVector3D location, bool isFalling = false, float fallingSpeed = 0.1f);

    int getSize();
    QVector3D getLocation();
    void move();
    void setFalling();
    bool getFalling();

    HitBox* getHitBox();
    void addHitBox(HitBox* hitbox);
private:
    bool isFalling;
    float fallingSpeed;

    BARRELTYPE type;
    int size;
    QVector3D location;

    HitBox* hitbox;
    QVector<HitBox*> otherHitBoxes;
    bool hasCollided();
    float sideSize;
};

#endif // BARREL_H
