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
    constexpr static float fallingConstant = -0.01f;
public:
    BulletView(QVector3D location, QVector3D flyingDirection, bool isBullet = true, QVector3D fallingDirection = QVector3D(0, fallingConstant, 0));
    void draw(bool isWireframe = false);
    void addHitBox(HitBox* hitbox);
    bool shouldDelete();
};

#endif // BULLETVIEW_H
