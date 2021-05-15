#ifndef WALL_H
#define WALL_H
#include <QVector>
class HitBox;
static enum DIRECTION {NORTH, EAST, SOUTH, WEST};
class Wall
{
public:
    Wall(double x1, double y1, double z1, double x2, double y2, double z2, DIRECTION direction);
    QVector<double>* getBottomLeft();
    QVector<double>* getBottomRight();
    QVector<double>* getTopLeft();
    QVector<double>* getTopRight();
    HitBox* getHitBox();
private:
    double x1, y1, z1, x2, y2, z2;
    HitBox* hitbox;

    DIRECTION direction;
};

#endif // WALL_H
