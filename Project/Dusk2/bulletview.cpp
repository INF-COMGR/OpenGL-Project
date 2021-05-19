#include "bulletview.h"
#include "bullet.h"
#include "util.h"
#include "hitbox.h"
#include "texture.h"

BulletView::BulletView(QVector3D location, QVector3D flyingDirection, bool isBullet, QVector3D fallingDirection)
{
    bullet = new Bullet(location, flyingDirection, fallingDirection, isBullet);
    texture = new Texture("bullet.jpeg");
}

void BulletView::draw(bool isWireframe) {

    float mcolor[] = { 1.0f, bullet->getIsBullet() ? 0.0f : 1.0f, bullet->getIsBullet() ? 0.0f : 1.0f, 1.0f };
    //if ()
        //mcolor = { 1.0f,0.5f,0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

    glEnable(GL_NORMALIZE);

    const float size = 0.2;
    texture->bindTexture();
    glPushMatrix();
        if (!bullet->getCollided())
            bullet->update();
        QVector3D location = bullet->getLocation();
        glTranslated(location.x(), location.y(), location.z());
        if (!isWireframe)
            glEnable(GL_LIGHTING);
        glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
            glTexCoord2d(0, 0);
            glVertex3d(0, size, 0);
            glTexCoord2d(0, 1);
            glVertex3d(size, 0, 0);
            glTexCoord2d(1, 0);
            glVertex3d(0, -size, 0);
            glTexCoord2d(1, 1);
            glVertex3d(-size, 0, 0);
        glEnd();
        glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
            glTexCoord2d(0, 0);
            glVertex3d(0, size, 0);
            glTexCoord2d(0, 1);
            glVertex3d(0, 0, size);
            glTexCoord2d(1, 0);
            glVertex3d(0, -size, 0);
            glTexCoord2d(1, 1);
            glVertex3d(0, 0, -size);
        glEnd();
    glPopMatrix();
    texture->unBindTexture();
}

void BulletView::addHitBox(HitBox* hitbox) {
    bullet->addHitBox(hitbox);
}

bool BulletView::shouldDelete() {
    return false;//this->bullet->getCollided();
}
