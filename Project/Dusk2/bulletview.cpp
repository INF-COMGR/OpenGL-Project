#include "bulletview.h"
#include "bullet.h"
#include "util.h"

BulletView::BulletView(QVector3D location, QVector3D flyingDirection)
{
    bullet = new Bullet(location, flyingDirection);
}

void BulletView::draw(bool isWireframe) {
    glPushMatrix();
        bullet->move();
        QVector3D location = bullet->getLocation();
        glTranslated(location.x(), location.y(), location.z());
        Util::drawSolidSphere(0.2, 25, 25);
    glPopMatrix();
}
