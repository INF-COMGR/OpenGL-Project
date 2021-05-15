#ifndef WALLVIEW_H
#define WALLVIEW_H
#include "wall.h"
#include <QVector3D>
class WallView
{
public:
    WallView(double x1, double y1, double z1, double x2, double y2, double z3, float red, float green, float blue);
    WallView(Wall* wall, float red, float green, float blue);
    void draw(bool isWireframe = false);
private:
    void addTexture();
    Wall* wall;
    float red, green, blue;
    QVector3D bottomLeft;
    QVector3D bottomRight;
    QVector3D topRight;
    QVector3D topLeft;
    QVector3D getNormal(QVector3D a, QVector3D b, QVector3D c);
    QVector3D normalize(QVector3D normal);
};

#endif // WALLVIEW_H
