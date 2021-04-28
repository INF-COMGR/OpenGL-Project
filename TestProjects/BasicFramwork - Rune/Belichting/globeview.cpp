#include "globeview.h"
#include <QOpenGLWidget>
#include "util.h"

GlobeView::GlobeView(float radius, float red, float yellow, float blue)
{
    globe = new Globe(radius, red, yellow, blue);
}

void GlobeView::Draw(unsigned long shading,unsigned long mode1, unsigned long material) {

    GLfloat color [] = {globe->getRed(), globe->getYellow(), globe->getBlue()};

    glShadeModel(shading);
    glMaterialfv ( mode1, material, color);

    Util::drawSolidSphere(globe->getRadius(), 50, 50);
}
