#include "barrelview.h"
#include "barrel.h"
#include "util.h"
#include <QCoreApplication>
#include <QTextStream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "hitbox.h"
#include "texture.h"

BarrelView::BarrelView(int size, QVector3D location)
{
    barrel = new Barrel(size, location);
    textureBody = new Texture("barrelBody.jpg");
    textureLid = new Texture("barrelLid.jpg");
}

HitBox* BarrelView::getHitBox() {
    return barrel->getHitBox();
}

void BarrelView::setFalling() {
    barrel->setFalling();
}

void BarrelView::addHitBox(HitBox* hitbox) {
    barrel->addHitBox(hitbox);
}

void BarrelView::draw(bool isWireframe)
{
    if (barrel->getHitBox()->getHitByBullet())
        barrel->getHitBox()->setInvalid();
    if (!this->getHitBox()->getHitByBullet())
        drawBarrel(isWireframe);
    else
        drawExplosion(isWireframe);
}

void BarrelView::drawBarrel(bool isWireframe) {
    glPushMatrix();
    int size = barrel->getSize();
    float alpha = size/4.0f;
    float beta = sqrt(3) * alpha;
    QVector3D location = barrel->getLocation();

    if (barrel->getFalling())
        barrel->move();

    glTranslated(location.x(), location.y(), location.z());
    QVector3D normal;

    // Bottom

    float mcolor[] = { 1.0f,1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

    glEnable(GL_NORMALIZE);

    textureLid->bindTexture();
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
    textureLid->unBindTexture();

     // Body
    textureBody->bindTexture();
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
    textureBody->unBindTexture();

    // Top
    textureLid->bindTexture();
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
    textureLid->unBindTexture();
    glPopMatrix();
}

void BarrelView::drawExplosion(bool isWireframe) {

}
