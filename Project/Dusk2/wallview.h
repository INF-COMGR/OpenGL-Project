#ifndef WALLVIEW_H
#define WALLVIEW_H
#include "wall.h"
#include <QWidget>
class WallView : public QWidget
{
public:
    WallView(double x1, double y1, double z1, double x2, double y2, double z3, float red, float green, float blue, DIRECTION direction);
    WallView(Wall* wall, float red, float green, float blue, DIRECTION direction);
    void draw(bool isWireframe = false);
    HitBox* getHitBox();
private:
    void initTextures();
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char* image;
    void addTexture();
    void shadersTest();

    Wall* wall;
    float red, green, blue;
};

#endif // WALLVIEW_H
