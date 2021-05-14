#include "barrelview.h"
#include "barrel.h"
#include "util.h"
#include <QCoreApplication>
#include <QTextStream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    bool textureForBody = true;
    bool textureForLid = false;
    QVector3D location = barrel->getLocation();
    glTranslated(location.x(), location.y(), location.z());

    glColor4f(1, 1, 1, 1);

    // Bottom
    addTexture(textureForLid);
    glEnable( GL_LIGHTING );
    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
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

void BarrelView::addTexture(bool forBody) {
    unsigned int texture;
    int width, height, nrChannels;
    QString path;
    if (forBody)
        path = {QCoreApplication::applicationDirPath() + "/../../../../Dusk2/barrelBody.jpg"};
    else
        path = {QCoreApplication::applicationDirPath() + "/../../../../Dusk2/barrelLid.jpg"};

    unsigned char *image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    } else {
        QTextStream out(stdout);
            out << stbi_failure_reason();
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

void BarrelView::getTexture() {
    /*int imageWidth = 0;
    int imageHeight = 0;
    unsigned char* image = SOIL_load_image*/
}
/*
void WallView::addTexture() {
    unsigned int texture;
    int width, height, nrChannels;

    //TODO: LOOK FOR SOLUTION FOR ABSOLUTE PATH
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
    std::cout << " " << path.toStdString() << " ";
    unsigned char *image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else {
        QTextStream out(stdout);
            out << stbi_failure_reason();
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
}*/
