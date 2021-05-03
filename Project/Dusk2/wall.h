#ifndef WALL_H
#define WALL_H
#include <QVector>

class Wall
{
public:
    Wall(double x1, double y1, double z1, double x2, double y2, double z2);
    QVector<double>* getBottomLeft();
    QVector<double>* getBottomRight();
    QVector<double>* getTopLeft();
    QVector<double>* getTopRight();

private:
    double x1, y1, z1, x2, y2, z2;
};

#endif // WALL_H
