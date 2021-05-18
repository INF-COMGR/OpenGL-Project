#ifndef BARRELVIEW_H
#define BARRELVIEW_H

#include <QVector3D>
class Barrel;
class HitBox;
class Texture;

class BarrelView
{
private:
    Barrel* barrel;
    Texture* textureBody;
    Texture* textureLid;

    void drawBarrel(bool isWireframe);
    void drawExplosion(bool isWireframe);
public:
    HitBox* getHitBox();
    BarrelView(int size, QVector3D location);
    void setFalling();
    void draw(bool isWireframe = false);
    void addHitBox(HitBox* hitbox);
};

#endif // BARRELVIEW_H
