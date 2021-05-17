#include "barrelview.h"
#include "barrel.h"

#include <QCoreApplication>
#include <QTextStream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

BarrelView::BarrelView(int size, QVector3D location)
{
    barrel = new Barrel(size, location);
    initTextures();
}

void BarrelView::setFalling() {
    barrel->setFalling();
}

void BarrelView::drawColor() {
    glPushMatrix();
    glDisable( GL_TEXTURE_2D );

    int size = barrel->getSize();
    float alpha = size/4.0f;
    float beta = sqrt(3) * alpha;
    QVector3D location = barrel->getLocation();

    if (barrel->getFalling()) {
        barrel->move();
    }

    glTranslated(location.x(), location.y(), location.z());
    //int temp[] = {*zgetUniqueColor(2)};
    //glColor3iv(temp);

    // Bottom
    glBegin( GL_POLYGON );
        glTexCoord2d(0 + 0.5, -2 * alpha + 0.5);
        glVertex3d(0, 0, -2 * alpha);

        glTexCoord2d(beta+  0.5, -alpha + 0.5);
        glVertex3d(beta, 0, -alpha);

        glTexCoord2d(beta + 0.5, alpha+ 0.5);
        glVertex3d(beta, 0, alpha);

        glTexCoord2d(0 + 0.5, 2 * alpha + 0.5);
        glVertex3d(0, 0, 2 * alpha);

        glTexCoord2d(-beta + 0.5, alpha+ 0.5);
        glVertex3d(-beta, 0, alpha);

        glTexCoord2d(-beta + 0.5, -alpha + 0.5);
        glVertex3d(-beta, 0, -alpha);
    glEnd();


     // Body
    glBegin( GL_POLYGON );
        glTexCoord2d( 0, 0);
        glVertex3d(0, 0, -2 * alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(0, size, -2 * alpha);
        glTexCoord2d(1, 0);
        glVertex3d(beta, 0, -alpha);
        glTexCoord2d( 1, 1);
        glVertex3d(beta, size, -alpha);

        glTexCoord2d( 0, 0);
        glVertex3d(beta, 0, alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(beta, size, alpha);
        glTexCoord2d( 1, 0);
        glVertex3d(0, 0, 2 * alpha);
        glTexCoord2d( 1, 1);
        glVertex3d(0, size, 2 * alpha);

        glTexCoord2d(0, 0);
        glVertex3d(-beta, 0, alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(-beta, size, alpha);
        glTexCoord2d( 1, 0);
        glVertex3d(-beta, 0, -alpha);
        glTexCoord2d( 1, 1);
        glVertex3d(-beta, size, -alpha);

        glTexCoord2d( 0, 0);
        glVertex3d(0, 0, -2 * alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(0, size, -2 * alpha);

    glEnd();

    // Top
    glBegin( GL_POLYGON );
        glTexCoord2d(0 + 0.5, -2 * alpha + 0.5);
        glVertex3d(0, size, -2 * alpha);
        glTexCoord2d(beta + 0.5, -alpha + 0.5);
        glVertex3d(beta, size, -alpha);
        glTexCoord2d(beta + 0.5, alpha + 0.5);
        glVertex3d(beta, size, alpha);
        glTexCoord2d(0 + 0.5, 2 * alpha + 0.5);
        glVertex3d(0, size, 2 * alpha);
        glTexCoord2d(-beta + 0.5, alpha + 0.5);
        glVertex3d(-beta, size, alpha);
        glTexCoord2d(-beta + 0.5, -alpha + 0.5);
        glVertex3d(-beta, size, -alpha);
    glEnd();

    glPopMatrix();

}

void BarrelView::draw(bool isWireframe)
{
    glPushMatrix();

    int size = barrel->getSize();
    float alpha = size/4.0f;
    float beta = sqrt(3) * alpha;
    bool textureForBody = true;
    bool textureForLid = false;
    QVector3D location = barrel->getLocation();

    if (barrel->getFalling()) {
        barrel->move();
    }

    glTranslated(location.x(), location.y(), location.z());
    QVector3D normal;
    // Bottom
    addTexture(textureForLid);
    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
        normal = QVector3D::normal(QVector3D{0,0,-2*alpha}, QVector3D{beta,0,-alpha});
        glNormal3f(normal[0], normal[1], normal[2]);
        glTexCoord2d(0 + 0.5, -2 * alpha + 0.5);
        glVertex3d(0, 0, -2 * alpha);

        normal = QVector3D::normal(QVector3D{beta,0,-alpha}, QVector3D{beta,0,alpha});
        glNormal3f(normal[0], normal[1], normal[2]);
        glTexCoord2d(beta+  0.5, -alpha + 0.5);
        glVertex3d(beta, 0, -alpha);

        normal = QVector3D::normal(QVector3D{beta,0,alpha}, QVector3D{0,0,2*alpha});
        glNormal3f(normal[0], normal[1], normal[2]);
        glTexCoord2d(beta + 0.5, alpha+ 0.5);
        glVertex3d(beta, 0, alpha);

        normal = QVector3D::normal(QVector3D{0,0,2*alpha}, QVector3D{-beta,0,alpha});
        glNormal3f(normal[0], normal[1], normal[2]);
        glTexCoord2d(0 + 0.5, 2 * alpha + 0.5);
        glVertex3d(0, 0, 2 * alpha);

        normal = QVector3D::normal(QVector3D{-beta,0,alpha}, QVector3D{-beta,0,-alpha});
        glNormal3f(normal[0], normal[1], normal[2]);
        glTexCoord2d(-beta + 0.5, alpha+ 0.5);
        glVertex3d(-beta, 0, alpha);

        normal = QVector3D::normal(QVector3D{-beta,0,-alpha}, QVector3D{0,0,-2*alpha});
        glNormal3f(normal[0], normal[1], normal[2]);
        glTexCoord2d(-beta + 0.5, -alpha + 0.5);
        glVertex3d(-beta, 0, -alpha);
    glEnd();


     // Body
    addTexture(textureForBody);
    glBegin( !isWireframe ? GL_QUAD_STRIP : GL_LINE_LOOP );
        glTexCoord2d( 0, 0);
        glVertex3d(0, 0, -2 * alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(0, size, -2 * alpha);
        glTexCoord2d(1, 0);
        glVertex3d(beta, 0, -alpha);
        glTexCoord2d( 1, 1);
        glVertex3d(beta, size, -alpha);

        glTexCoord2d( 0, 0);
        glVertex3d(beta, 0, alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(beta, size, alpha);
        glTexCoord2d( 1, 0);
        glVertex3d(0, 0, 2 * alpha);
        glTexCoord2d( 1, 1);
        glVertex3d(0, size, 2 * alpha);

        glTexCoord2d(0, 0);
        glVertex3d(-beta, 0, alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(-beta, size, alpha);
        glTexCoord2d( 1, 0);
        glVertex3d(-beta, 0, -alpha);
        glTexCoord2d( 1, 1);
        glVertex3d(-beta, size, -alpha);

        glTexCoord2d( 0, 0);
        glVertex3d(0, 0, -2 * alpha);
        glTexCoord2d( 0, 1);
        glVertex3d(0, size, -2 * alpha);

    glEnd();

    // Top
    addTexture(textureForLid);
    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
        glTexCoord2d(0 + 0.5, -2 * alpha + 0.5);
        glVertex3d(0, size, -2 * alpha);
        glTexCoord2d(beta + 0.5, -alpha + 0.5);
        glVertex3d(beta, size, -alpha);
        glTexCoord2d(beta + 0.5, alpha + 0.5);
        glVertex3d(beta, size, alpha);
        glTexCoord2d(0 + 0.5, 2 * alpha + 0.5);
        glVertex3d(0, size, 2 * alpha);
        glTexCoord2d(-beta + 0.5, alpha + 0.5);
        glVertex3d(-beta, size, alpha);
        glTexCoord2d(-beta + 0.5, -alpha + 0.5);
        glVertex3d(-beta, size, -alpha);
    glEnd();

    glPopMatrix();
}

void BarrelView::initTextures() {
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/barrelBody.jpg"};

    //TEXTURE SIDE BARREL
    imageSide = stbi_load(path.toStdString().c_str(), &widthSide, &heightSide, &nrChannelsSide, 0);
    glGenTextures(1, &textureSide);
    glBindTexture(GL_TEXTURE_2D, textureSide);

    if (imageSide != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthSide, heightSide, 0, GL_RGB, GL_UNSIGNED_BYTE, imageSide);

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

    //TEXTURE TOP BARREL
    path = {QCoreApplication::applicationDirPath() + "/../../../../Dusk2/barrelLid.jpg"};

    imageTop = stbi_load(path.toStdString().c_str(), &widthTop, &heightTop, &nrChannelsTop, 0);
    glGenTextures(1, &textureTop);
    glBindTexture(GL_TEXTURE_2D, textureTop);

    if (imageTop != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthTop, heightTop, 0, GL_RGB, GL_UNSIGNED_BYTE, imageTop);

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

void BarrelView::addTexture(bool forBody) {
    glEnable( GL_TEXTURE_2D );
    if (forBody)
        glBindTexture( GL_TEXTURE_2D , textureSide );
    else
        glBindTexture( GL_TEXTURE_2D , textureTop );
}

int* BarrelView::getUniqueColor(int i) {
    // Convert "i", the integer mesh ID, into an RGB color
    int r = (i & 0x000000FF) >>  0;
    int g = (i & 0x0000FF00) >>  8;
    int b = (i & 0x00FF0000) >> 16;

    int color[] = {r, g, b};
    return color;
}

