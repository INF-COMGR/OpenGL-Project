#ifndef ROOMVIEW_H
#define ROOMVIEW_H
#include "room.h"
class WallView;
<<<<<<< HEAD
=======
class FloorView;
>>>>>>> feature-room

class RoomView
{
public:
    RoomView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue);
<<<<<<< HEAD
    void Draw();
=======
    void draw();
>>>>>>> feature-room
private:
    Room* room;
    WallView* wall1;
    WallView* wall2;
    WallView* wall3;
    WallView* wall4;
<<<<<<< HEAD
=======
    FloorView* floor;
>>>>>>> feature-room

};

#endif // ROOMVIEW_H
