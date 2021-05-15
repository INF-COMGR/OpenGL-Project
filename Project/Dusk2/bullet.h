#ifndef BULLET_H
#define BULLET_H
#include <QVector3D>

class Bullet
{
private:
    QVector3D location;
    QVector3D flyingDirection;
public:
    void move();
    Bullet(QVector3D location, QVector3D flyingDirection);
    QVector3D getLocation();
};

#endif // BULLET_H
