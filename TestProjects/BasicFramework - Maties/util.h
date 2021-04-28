#ifndef UTIL_H
#define UTIL_H

#include <glu.h>
#include <QVector3D>

class Util
{
public:

    static void drawSolidSphere(GLdouble radius, GLint slices, GLint stacks)
    {
      GLUquadricObj* quadric = gluNewQuadric();

      gluQuadricDrawStyle(quadric, GLU_FILL);
      gluSphere(quadric, radius, slices, stacks);

      gluDeleteQuadric(quadric);
    }

    static void drawSolidCuboid(QVector3D topLeft, QVector3D bottomRight) {
        glBegin(GL_QUAD_STRIP);
            glVertex3f(topLeft.x(), topLeft.y(), topLeft.z());
            glVertex3f(bottomRight.x(), topLeft.y(), topLeft.z());
            glVertex3f(topLeft.x(), topLeft.y(), bottomRight.z());
            glVertex3f(bottomRight.x(), topLeft.y(), bottomRight.z());

            glVertex3f(topLeft.x(), bottomRight.y(), bottomRight.z());
            glVertex3f(bottomRight.x(), bottomRight.y(), bottomRight.z());

            glVertex3f(topLeft.x(), bottomRight.y(), topLeft.z());
            glVertex3f(bottomRight.x(), bottomRight.y(), topLeft.z());

            glVertex3f(topLeft.x(), topLeft.y(), topLeft.z());
            glVertex3f(bottomRight.x(), topLeft.y(), topLeft.z());
        glEnd();
        glBegin(GL_QUADS);
            glVertex3f(topLeft.x(), topLeft.y(), topLeft.z());
            glVertex3f(topLeft.x(), topLeft.y(), bottomRight.z());
            glVertex3f(topLeft.x(), bottomRight.y(), bottomRight.z());
            glVertex3f(topLeft.x(), bottomRight.y(), topLeft.z());

            glVertex3f(bottomRight.x(), topLeft.y(), topLeft.z());
            glVertex3f(bottomRight.x(), topLeft.y(), bottomRight.z());
            glVertex3f(bottomRight.x(), bottomRight.y(), bottomRight.z());
            glVertex3f(bottomRight.x(), bottomRight.y(), topLeft.z());
        glEnd();
    }
};

#endif // UTIL_H
