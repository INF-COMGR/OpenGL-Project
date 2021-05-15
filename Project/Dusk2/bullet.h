#ifndef BULLET_H
#define BULLET_H
#include <QVector3D>
#include <QVector>
class HitBox;

class Bullet
{
private:
    QVector3D location;
    QVector3D flyingDirection;
    bool hasCollided();
    bool isCollided = false;
    void move();
public:
    void update();
    bool getCollided();
    Bullet(QVector3D location, QVector3D flyingDirection);
    QVector3D getLocation();
    void addHitBox(HitBox* hitbox);
    QVector<HitBox*> hitboxes;
};

#endif // BULLET_H
