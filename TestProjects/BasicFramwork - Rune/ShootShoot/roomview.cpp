#include "roomview.h"
#include "util.h"

RoomView::RoomView(float width, float length)
{
    room = new Room(width, length);
}

void RoomView::Draw() {
    float width = room->getWidth();
    float length = room->getLength();
    glShadeModel( GL_FLAT );
    glColor3f( 0.4f, 0.2f, 0.1f );
    glBegin(GL_QUADS);
    /* Floor */
//    glVertex3f(-width,-length,-width);
//    glVertex3f(width,-width,-width);
//    glVertex3f(width,-width,width);
//    glVertex3f(-width,-width,width);
//    /* Ceiling */
//    glVertex3f(-width,width,-width);
//    glVertex3f(width,width,-width);
//    glVertex3f(width,width,width);
//    glVertex3f(-width,width,width);
    /* Walls */

    glVertex3f(-width,-width,width);
    glVertex3f(width,-width,width);
    glVertex3f(width,width,width);
    glVertex3f(-width,width,width);

    glVertex3f(-width,-width,-width);
    glVertex3f(width,-width,-width);
    glVertex3f(width,width,-width);
    glVertex3f(-width,width,-width);

    glVertex3f(width,width,width);
    glVertex3f(width,-width,width);
    glVertex3f(width,-width,-width);
    glVertex3f(width,width,-width);

    glVertex3f(-width,width,width);
    glVertex3f(-width,-width,width);
    glVertex3f(-width,-width,-width);
    glVertex3f(-width,width,-width);

    glEnd();
}
