#include "shotgunview.h"
#include "shotgun.h"
#include "util.h"
#include <QCoreApplication>
#include <QTextStream>
#include "stb_image.h"

ShotgunView::ShotgunView()
{
    shotgun = new Shotgun();
    initTextures();
}

void ShotgunView::draw(bool isWireframe)
{
    glEnable(GL_NORMALIZE);
    glPushMatrix();
        glTranslated(0, -0.5, -2);

        if (!isWireframe)
            addTexture();

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
    glPopMatrix();
}

void ShotgunView::initTextures() {
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/shotgun.jpg"};

    //TEXTURE SIDE BARREL
    image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    } else {
        QTextStream out(stdout);
            out << stbi_failure_reason();
    }

    //stbi_image_free(image);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // use our previously defined texture

}

void ShotgunView::addTexture() {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D , texture );
}


