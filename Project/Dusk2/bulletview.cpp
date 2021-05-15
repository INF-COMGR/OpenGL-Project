#include "bulletview.h"
#include "bullet.h"
#include "util.h"
#include "hitbox.h"

BulletView::BulletView(QVector3D location, QVector3D flyingDirection)
{
    bullet = new Bullet(location, flyingDirection);
}

void BulletView::draw(bool isWireframe) {
    const float size = 0.2;
    glPushMatrix();
        if (!bullet->getCollided())
            bullet->update();
        QVector3D location = bullet->getLocation();
        glTranslated(location.x(), location.y(), location.z());
        glEnable( GL_LIGHTING );
        glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
            glVertex3d(0, size, 0);
            glVertex3d(size, 0, 0);
            glVertex3d(0, -size, 0);
            glVertex3d(-size, 0, 0);
        glEnd();
        glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
            glVertex3d(0, size, 0);
            glVertex3d(0, 0, size);
            glVertex3d(0, -size, 0);
            glVertex3d(0, 0, -size);
        glEnd();
    glPopMatrix();
}

void BulletView::addHitBox(HitBox* hitbox) {
    bullet->addHitBox(hitbox);
}
