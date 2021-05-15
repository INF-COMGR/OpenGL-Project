#ifndef BARREL_H
#define BARREL_H

#include "QVector"
#include "QVector3D"

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
private:
    bool isFalling;
    float fallingSpeed;

    BARRELTYPE type;
    int size;
    QVector3D location;
};

#endif // BARREL_H
