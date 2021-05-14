#ifndef BARRELVIEW_H
#define BARRELVIEW_H

#include <QVector3D>
class Barrel;

class BarrelView
{
private:
    Barrel* barrel;
    void getTexture();
    void addTexture(bool forBody);
public:
    BarrelView(int size, QVector3D location);
    void draw(bool isWireframe = false);
};

#endif // BARRELVIEW_H
