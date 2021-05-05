#ifndef FLOOR_H
#define FLOOR_H
#include <QVector>

class Floor
{
public:
    Floor(double x1, double z1, double x2, double z2);
    QVector<double>* getBottomLeft();
    QVector<double>* getBottomRight();
    QVector<double>* getTopLeft();
    QVector<double>* getTopRight();
private:
     double x1, z1, x2, z2;
};

#endif // FLOOR_H
