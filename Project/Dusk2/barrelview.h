#ifndef BARRELVIEW_H
#define BARRELVIEW_H
#include "util.h"
#include <QVector3D>
class Barrel;

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

public:
    BarrelView(int size, QVector3D location);
    void setFalling();
    void draw(bool isWireframe = false);
    int* getUniqueColor(int i);
    void drawColor();
};

#endif // BARRELVIEW_H
