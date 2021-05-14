#include "wallview.h"
#include "util.h"
//#include <QTextStream>
#include <QCoreApplication>
//#include <iostream>

#include "stb_image.h"

WallView::WallView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue)
{
    this->wall = new Wall(x1, y1, z1, x2, y2, z2);
    this->red = red;
    this->green = green;
    this->blue = blue;
    initTextures();
}

WallView::WallView(Wall* wall, float red, float green, float blue) {
    this->wall = wall;
    this->red = red;
    this->green = green;
    this->blue = blue;
    initTextures();
}

void WallView::draw(bool isWireframe) {
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

    if (!isWireframe)
        addTexture();

    glColor4f((blue)/255.0f,
              (green)/255.0f,
              (blue)/255.0f,
              1.0f);
    glBegin(!isWireframe ? GL_QUADS : GL_LINE_LOOP);
        //glNormal3f(1.0, 1.0, 1.0);
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z1);
        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y2,z2);
        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x3,y3,z3);
        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x4,y4,z4);
    glEnd();
    glColor4f(1, 1, 1, 1);
}

void WallView::initTextures() {
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
    //std::cout << " " << path.toStdString() << " ";
    image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else {
        perror( stbi_failure_reason() );
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

void WallView::addTexture() {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D , texture );

}

