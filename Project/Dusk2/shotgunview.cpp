#include "shotgunview.h"
#include "shotgun.h"
#include "util.h"

ShotgunView::ShotgunView()
{
    shotgun = new Shotgun();
}

void ShotgunView::draw(bool isWireframe)
{
    glEnable(GL_NORMALIZE);
    glPushMatrix();
        glTranslated(0, -0.5, -2);

        if (!isWireframe) {
            glBegin( GL_QUAD_STRIP );
                //left side - left barrel
                glVertex3d(-0.2, 0, 2);
                glVertex3d(-0.2, 0, -1);
                glVertex3d(-0.1, 0.1, 2);
                glVertex3d(-0.1, 0.1, -1);

                //right side - right barrel
                glVertex3d(0, 0, 2);
                glVertex3d(0, 0, -1);

                //left side - right barrel
                glVertex3d(0.1, 0.1, 2);
                glVertex3d(0.1, 0.1, -1);

                //right side - right barrel
                glVertex3d(0.2, 0, 2);
                glVertex3d(0.2, 0, -1);

            glEnd();
        } else {
            glBegin( GL_LINE_LOOP );
                //left side - left barrel
                glVertex3d(-0.2, 0, 2);
                glVertex3d(-0.2, 0, -1);
                glVertex3d(-0.1, 0.1, -1);
                glVertex3d(-0.1, 0.1, 2);
            glEnd();
            glBegin( GL_LINE_LOOP );
                //right side - right barrel
                glVertex3d(-0.1, 0.1, 2);
                glVertex3d(-0.1, 0.1, -1);
                glVertex3d(0, 0, -1);
                glVertex3d(0, 0, 2);
            glEnd();
            glBegin( GL_LINE_LOOP );
                //left side - right barrel
                glVertex3d(0, 0, 2);
                glVertex3d(0, 0, -1);
                glVertex3d(0.1, 0.1, -1);
                glVertex3d(0.1, 0.1, 2);
            glEnd();
            glBegin( GL_LINE_LOOP );
                //right side - right barrel
                glVertex3d(0.1, 0.1, 2);
                glVertex3d(0.1, 0.1, -1);
                glVertex3d(0.2, 0, -1);
                glVertex3d(0.2, 0, 2);
            glEnd();
        }
    glPopMatrix();
}

