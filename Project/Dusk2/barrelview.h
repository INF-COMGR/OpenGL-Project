#ifndef BARRELVIEW_H
#define BARRELVIEW_H

#include <QVector3D>
class Barrel;
class HitBox;

class BarrelView
{
private:
    Barrel* barrel;
    void addTexture(bool forBody);
    void initTextures();
    unsigned int textureSide;
    int widthSide, heightSide, nrChannelsSide;
    unsigned char* imageSide;

    unsigned int textureTop;
    int widthTop, heightTop, nrChannelsTop;
    unsigned char* imageTop;

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
