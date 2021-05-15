#ifndef FLOOR_H
#define FLOOR_H
#include <QVector3D>

class Floor
{
public:
    Floor(double x1, double z1, double x2, double z2);
    QVector3D* getBottomLeft();
    QVector3D* getBottomRight();
    QVector3D* getTopLeft();
    QVector3D* getTopRight();
private:
     double x1, z1, x2, z2;
};

#endif // FLOOR_H
