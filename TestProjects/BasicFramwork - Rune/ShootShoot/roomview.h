#ifndef ROOMVIEW_H
#define ROOMVIEW_H
#include "room.h"


class RoomView
{
public:
    RoomView(float width, float length);
    void Draw();
private:
    Room* room;
};

#endif // ROOMVIEW_H
