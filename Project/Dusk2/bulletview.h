#ifndef BULLETVIEW_H
#define BULLETVIEW_H
#include <QVector3D>
class Bullet;
class HitBox;

class BulletView
{
private:
    Bullet* bullet;

public:
    BulletView(QVector3D location, QVector3D flyingDirection);
    void draw(bool isWireframe = false);
    void addHitBox(HitBox* hitbox);
};

#endif // BULLETVIEW_H
