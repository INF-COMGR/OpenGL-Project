#include "barrelview.h"
#include "barrel.h"
#include "util.h"
#define STB_IMAGE_IMPLEMENTATION

BarrelView::BarrelView(int size, QVector3D location)
{
    barrel = new Barrel(size, location);
}

void BarrelView::draw(bool isWireframe)
{
    glPushMatrix();
    int size = barrel->getSize();
    float alpha = size/4.0f;
    float beta = sqrt(3) * alpha;

    QVector3D location = barrel->getLocation();
    glTranslated(location.x(), location.y(), location.z());

    glEnable( GL_LIGHTING );
    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
        glVertex3d(0, 0, -2 * alpha);
        glVertex3d(beta, 0, -alpha);
        glVertex3d(beta, 0, alpha);
        glVertex3d(0, 0, 2 * alpha);
        glVertex3d(-beta, 0, alpha);
        glVertex3d(-beta, 0, -alpha);
    glEnd();

    glBegin( !isWireframe ? GL_QUAD_STRIP : GL_LINE_LOOP );
        glVertex3d(0, 0, -2 * alpha);
        glVertex3d(0, size, -2 * alpha);
        glVertex3d(beta, 0, -alpha);
        glVertex3d(beta, size, -alpha);
        glVertex3d(beta, 0, alpha);
        glVertex3d(beta, size, alpha);
        glVertex3d(0, 0, 2 * alpha);
        glVertex3d(0, size, 2 * alpha);
        glVertex3d(-beta, 0, alpha);
        glVertex3d(-beta, size, alpha);
        glVertex3d(-beta, 0, -alpha);
        glVertex3d(-beta, size, -alpha);
    glEnd();

    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
        glVertex3d(0, size, -2 * alpha);
        glVertex3d(beta, size, -alpha);
        glVertex3d(beta, size, alpha);
        glVertex3d(0, size, 2 * alpha);
        glVertex3d(-beta, size, alpha);
        glVertex3d(-beta, size, -alpha);
    glEnd();

    glPopMatrix();
}

void BarrelView::getTexture() {
    /*int imageWidth = 0;
    int imageHeight = 0;
    unsigned char* image = SOIL_load_image*/
}
