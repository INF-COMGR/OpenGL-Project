#ifndef BARRELVIEW_H
#define BARRELVIEW_H

#include <QVector3D>
#include <QVector>
class Barrel;
class HitBox;
class Texture;;
class BulletView;

class BarrelView
{
private:
    Barrel* barrel;
    Texture* textureBody;
    Texture* textureLid;

    QVector<BulletView*> shrapnel;
    int bulletAmount;
    const int BULLET_MAX = 10;
    const float SPEED_MAX = 0.5;

    bool shrapnelCreated = false;

    void drawBarrel(bool isWireframe);
    void drawExplosion(bool isWireframe);
    void initShrapnel();
public:
    HitBox* getHitBox();
    BarrelView(int size, QVector3D location);
    void setFalling();
    void draw(bool isWireframe = false);
    void addHitBox(HitBox* hitbox);
};

#endif // BARRELVIEW_H
