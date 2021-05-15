#ifndef FLOORVIEW_H
#define FLOORVIEW_H
#include "floor.h"
#include <QVector3D>
class FloorView
{
public:
    FloorView(double x1, double z1, double x2, double z2, float red, float green, float blue);
    FloorView(Floor* floor, float red, float green, float blue);
    void draw(bool isWirefram = false);
private:
    void addTexture();
    Floor* floor;
    float red, green, blue;
    QVector3D getNormal(QVector3D a, QVector3D b, QVector3D c);
    QVector3D normalize(QVector3D normal);
};

#endif // FLOORVIEW_H
