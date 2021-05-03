#include "roomview.h"
#include "util.h"
#include "wallview.h"
RoomView::RoomView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue)
{
    room = new Room(x1, y1, z1, x2, y2, z2);
    this->wall1 = new WallView(room->getWall1(), red, green, blue);
    this->wall2 = new WallView(room->getWall2(), red, green, blue);
    this->wall3 = new WallView(room->getWall3(), red, green, blue);
    this->wall4 = new WallView(room->getWall4(), red, green, blue);
}

void RoomView::Draw() {
    this->wall1->Draw();
    this->wall2->Draw();
    this->wall3->Draw();
    this->wall4->Draw();
}