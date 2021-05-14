#ifndef WALLVIEW_H
#define WALLVIEW_H
#include "wall.h"

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
};

#endif // WALLVIEW_H
