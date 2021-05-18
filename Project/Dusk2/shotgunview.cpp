#include "shotgunview.h"
#include "shotgun.h"
#include "util.h"
#include <QCoreApplication>
#include <QTextStream>
#include "stb_image.h"
#include "texture.h"

ShotgunView::ShotgunView()
{
    shotgun = new Shotgun();
    texture = new Texture("shotgun.jpg");
}

void ShotgunView::draw(bool isWireframe)
{
    float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
    glEnable(GL_NORMALIZE);
    glPushMatrix();
        glTranslated(0, -0.5, -2);

        if (!isWireframe)
            texture->bindTexture();

        if (!isWireframe) {
            glBegin( GL_QUADS );
                //left side - left barrel
                glTexCoord2d(0, 0);
                glVertex3d(-0.2, 0, 2);
                glTexCoord2d(0, 1);
                glVertex3d(-0.2, 0, -1);
                glTexCoord2d(0.25, 0);
                glVertex3d(-0.1, 0.1, -1);
                glTexCoord2d(0.25, 1);
                glVertex3d(-0.1, 0.1, 2);


                //right side - right barrel

                glTexCoord2d(0, 0);
                glVertex3d(-0.1, 0.1, 2);
                glTexCoord2d(0, 1);
                glVertex3d(-0.1, 0.1, -1);
                glTexCoord2d(0.25, 0);
                glVertex3d(0, 0, -1);
                glTexCoord2d(0.25, 1);
                glVertex3d(0, 0, 2);

                //left side - right barrel
                glTexCoord2d(0, 0);
                glVertex3d(0, 0, 2);
                glTexCoord2d(0, 1);
                glVertex3d(0, 0, -1);
                glTexCoord2d(0.25, 0);
                glVertex3d(0.1, 0.1, -1);
                glTexCoord2d(0.25, 1);
                glVertex3d(0.1, 0.1, 2);

                //right side - right barrel

                glTexCoord2d(0, 0);
                glVertex3d(0.1, 0.1, 2);
                glTexCoord2d(0, 1);
                glVertex3d(0.1, 0.1, -1);
                glTexCoord2d(0.25, 0);
                glVertex3d(0.2, 0, -1);
                glTexCoord2d(0.25, 1);
                glVertex3d(0.2, 0, 2);

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
    texture->unBindTexture();
    glPopMatrix();
}



