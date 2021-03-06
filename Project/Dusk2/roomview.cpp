#include "roomview.h"
#include "util.h"
#include "wallview.h"
#include "floorview.h"
#include "hitbox.h"
#include <QVector>

RoomView::RoomView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue)
{
    room = new Room(x1, y1, z1, x2, y2, z2);
    this->wall1 = new WallView(room->getWall1(), red, green, blue, DIRECTION::EAST);
    this->wall2 = new WallView(room->getWall2(), red, green, blue, DIRECTION::NORTH);
    this->wall3 = new WallView(room->getWall3(), red, green, blue, DIRECTION::WEST);
    this->wall4 = new WallView(room->getWall4(), red, green, blue, DIRECTION::SOUTH);
    this->floor = new FloorView(room->getFloor(), red, green, blue);
}

void RoomView::draw(bool isWireframe) {
    glPushMatrix();
        this->wall1->draw(isWireframe);
        this->wall2->draw(isWireframe);
        this->wall3->draw(isWireframe);
        this->wall4->draw(isWireframe);
        this->floor->draw(isWireframe);
    glPopMatrix();
}

QVector<HitBox*> RoomView::getHitBoxes() {
    QVector<HitBox*> hitboxes = QVector<HitBox*>{};
    hitboxes.append(floor->getHitBox());
    hitboxes.append(wall1->getHitBox());
    hitboxes.append(wall2->getHitBox());
    hitboxes.append(wall3->getHitBox());
    hitboxes.append(wall4->getHitBox());
    return hitboxes;
}
