#include "floorview.h"
#include "util.h"
//#include <QTextStream>
#include <QCoreApplication>
//#include <iostream>

#include "stb_image.h"

FloorView::FloorView(double x1, double z1, double x2, double z2, float red, float green, float blue) {
    this->floor = new Floor(x1, z1, x2, z2);
    this->red = red;
    this->green = green;
    this->blue = blue;
}

FloorView::FloorView(Floor* floor, float red, float green, float blue) {
    this->floor = floor;
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void FloorView::draw(bool isWireframe) {
    QVector<double> bottomLeft = *floor->getBottomLeft();
    double x1 = bottomLeft[0];
    double y1 = bottomLeft[1];
    double z1 = bottomLeft[2];

    QVector<double> bottomRight = *floor->getBottomRight();
    double x2 = bottomRight[0];
    double y2 = bottomRight[1];
    double z2 = bottomRight[2];

    QVector<double> topRight = *floor->getTopRight();
    double x3 = topRight[0];
    double y3 = topRight[1];
    double z3 = topRight[2];

    QVector<double> topLeft = *floor->getTopLeft();
    double x4 = topLeft[0];
    double y4 = topLeft[1];
    double z4 = topLeft[2];

    if (!isWireframe)
        addTexture();

    glColor4f((blue)/255.0f,
              (green)/255.0f,
              (blue)/255.0f,
              1.0f);
    glBegin( !isWireframe ? GL_QUADS : GL_LINE_LOOP );
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z1);
        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y2,z2);
        glTexCoord2d( 5.0, 0.0 );
        glVertex3f(x3,y3,z3);
        glTexCoord2d( 5.0, 5.0 );
        glVertex3f(x4,y4,z4);
    glEnd();
    glColor4f(1, 1, 1, 1);
}

void FloorView::addTexture() {

    unsigned int texture;
    int width, height, nrChannels;

    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/grass.jpg"};
    //std::cout << " " << path.toStdString() << " ";
    unsigned char *image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else {
        perror(stbi_failure_reason() );
    }
    stbi_image_free(image);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // use our previously defined texture
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D , texture );
}

