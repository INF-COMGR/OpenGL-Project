#ifndef BULLETVIEW_H
#define BULLETVIEW_H
#include <QVector3D>
class Bullet;
class HitBox;
class Texture;

class BulletView
{
private:
    Bullet* bullet;
    Texture* texture;

public:
    BulletView(QVector3D location, QVector3D flyingDirection);
    void draw(bool isWireframe = false);
    void addHitBox(HitBox* hitbox);
};

#endif // BULLETVIEW_H
