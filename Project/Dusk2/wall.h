#ifndef WALL_H
#define WALL_H
#include <QVector3D>

class Wall
{
public:
    Wall(double x1, double y1, double z1, double x2, double y2, double z2);
    QVector3D* getBottomLeft();
    QVector3D* getBottomRight();
    QVector3D* getTopLeft();
    QVector3D* getTopRight();

private:
    double x1, y1, z1, x2, y2, z2;
};

#endif // WALL_H
