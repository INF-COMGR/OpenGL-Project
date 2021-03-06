#ifndef FLOORVIEW_H
#define FLOORVIEW_H
#include "floor.h"
class Texture;

class FloorView
{
public:
    FloorView(double x1, double z1, double x2, double z2, float red, float green, float blue);
    FloorView(Floor* floor, float red, float green, float blue);
    void draw(bool isWirefram = false);
    HitBox* getHitBox();
private:
    Texture* texture;
    Floor* floor;
    float red, green, blue;
};

#endif // FLOORVIEW_H
