#ifndef ROOM_H
#define ROOM_H


class Room
{
public:
    Room(float width, float length);
    float getLength();
    float getWidth();

private:
    float width, length;
};

#endif // ROOM_H
