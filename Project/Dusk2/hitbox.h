#ifndef HITBOX_H
#define HITBOX_H
#include <QVector3D>

class HitBox
{
private:
    QVector3D topleftCorner;
    QVector3D bottomRightCorner;
    bool wasHitByBullet = false;
    bool isInvalid = false;
public:
    bool getHitByBullet();
    void setHitByBullet();
    void setInvalid();
    QVector3D getTopLeft();
    QVector3D getBottomRight();
    HitBox(QVector3D topLeft, QVector3D bottomRight);
    bool isPointInside(QVector3D point);
    bool isHitBoxInside(HitBox box);
    void update(QVector3D topleft, QVector3D bottomRight);
};

#endif // HITBOX_H
