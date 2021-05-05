#ifndef BARREL_H
#define BARREL_H

#include "QVector"
#include "QVector3D"

class Barrel
{
public:
    enum BARRELTYPE { NORMAL, FIREBARREL, EXPLOSIVE };
    Barrel(int size, QVector3D location);

    int getSize();
    QVector3D getLocation();
private:
    BARRELTYPE type;
    int size;
    QVector3D location;
};

#endif // BARREL_H
