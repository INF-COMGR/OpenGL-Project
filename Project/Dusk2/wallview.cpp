#include "wallview.h"
#include "util.h"

WallView::WallView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue)
{
    this->wall = new Wall(x1, y1, z1, x2, y2, z2);
    this->red = red;
    this->green = green;
    this->blue = blue;
}

WallView::WallView(Wall* wall, float red, float green, float blue) {
    this->wall = wall;
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void WallView::Draw() {
    QVector<double> bottomLeft = *wall->getBottomLeft();
    double x1 = bottomLeft[0];
    double y1 = bottomLeft[1];
    double z1 = bottomLeft[2];

    QVector<double> bottomRight = *wall->getBottomRight();
    double x2 = bottomRight[0];
    double y2 = bottomRight[1];
    double z2 = bottomRight[2];

    QVector<double> topRight = *wall->getTopRight();
    double x3 = topRight[0];
    double y3 = topRight[1];
    double z3 = topRight[2];

    QVector<double> topLeft = *wall->getTopLeft();
    double x4 = topLeft[0];
    double y4 = topLeft[1];
    double z4 = topLeft[2];

//    double texCoords[] = { x1, y1, z1, x3, y3, z3};
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glBegin(GL_QUADS);
    glColor4f(red/255.0f,
              green/255.0f,
              blue/255.0f,
              1.0f);
    glVertex3f(x1,y1,z1);
    glVertex3f(x2,y2,z2);
    glVertex3f(x3,y3,z3);
    glVertex3f(x4,y4,z4);
    glEnd();
    glColor4f(1, 1, 1, 1);
}

