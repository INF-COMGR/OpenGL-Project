#ifndef FLOOR_H
#define FLOOR_H
#include <QVector>
class HitBox;

class Floor
{
public:
    Floor(double x1, double z1, double x2, double z2);
    QVector<double>* getBottomLeft();
    QVector<double>* getBottomRight();
    QVector<double>* getTopLeft();
    QVector<double>* getTopRight();
    HitBox* getHitBox();
private:
     double x1, z1, x2, z2;
     HitBox* hitbox;
};

#endif // FLOOR_H
