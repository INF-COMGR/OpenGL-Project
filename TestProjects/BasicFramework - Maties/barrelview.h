#ifndef BARRELVIEW_H
#define BARRELVIEW_H

#include <QVector3D>
class Barrel;

class BarrelView
{
private:
    Barrel* barrel;
    void getTexture();
public:
    BarrelView(int size, QVector3D location);
    void draw();
};

#endif // BARRELVIEW_H
