#include "wallview.h"
#include "util.h"
//#include <QTextStream>
#include <QCoreApplication>
//#include <iostream>
#include "hitbox.h"
#include "stb_image.h"
#include "texture.h"

#define highp
#define mediump
#define lowp

WallView::WallView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue, DIRECTION direction)
{
    this->wall = new Wall(x1, y1, z1, x2, y2, z2, direction);
    this->red = red;
    this->green = green;
    this->blue = blue;
    texture = new Texture("wall.jpg");
    //initTextures();
}

WallView::WallView(Wall* wall, float red, float green, float blue, DIRECTION direction) {
    this->wall = wall;
    this->red = red;
    this->green = green;
    this->blue = blue;
    //initTextures();
    texture = new Texture("wall.jpg");
}

void WallView::draw(bool isWireframe) {
    QVector3D bottomLeft = *wall->getBottomLeft();
    double x1 = bottomLeft[0];
    double y1 = bottomLeft[1];
    double z1 = bottomLeft[2];

    QVector3D bottomRight = *wall->getBottomRight();
    double x2 = bottomRight[0];
    double y2 = bottomRight[1];
    double z2 = bottomRight[2];

    QVector3D topRight = *wall->getTopRight();
    double x3 = topRight[0];
    double y3 = topRight[1];
    double z3 = topRight[2];

    QVector3D topLeft = *wall->getTopLeft();
    double x4 = topLeft[0];
    double y4 = topLeft[1];
    double z4 = topLeft[2];

    if (!isWireframe)
        texture->bindTexture();

    float mcolor[] = { blue/255.0f, (green)/255.0f, (blue)/255.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

    glEnable(GL_NORMALIZE);

    glBegin(!isWireframe ? GL_QUADS : GL_LINE_LOOP);
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z1);

        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y2,z2);

        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x3,y3,z3);

        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x4,y4,z4);
    glEnd();

    texture->unBindTexture();


}

void WallView::initTextures() {
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
    //std::cout << " " << path.toStdString() << " ";
    image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

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
    glBindTexture( GL_TEXTURE_2D , textureID );
}

HitBox* WallView::getHitBox() {
    return wall->getHitBox();
}

void WallView::shadersTest() {

}

