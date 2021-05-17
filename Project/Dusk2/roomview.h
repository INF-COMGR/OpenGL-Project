#ifndef ROOMVIEW_H
#define ROOMVIEW_H
#include "room.h"
class WallView;
class FloorView;


class RoomView
{
public:
    RoomView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue);
    void draw(bool isWireframe = false);
    QVector<HitBox*> getHitBoxes();
private:
    Room* room;
    WallView* wall1;
    WallView* wall2;
    WallView* wall3;
    WallView* wall4;
    FloorView* floor;

};

#endif // ROOMVIEW_H
