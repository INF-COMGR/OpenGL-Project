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
    QVector3D fallingDirection;
    bool hasCollided();
    bool isCollided = false;
    void move();
    bool isBullet;
public:
    void update();
    bool getCollided();
    Bullet(QVector3D location, QVector3D flyingDirection, QVector3D fallingDirection, bool isBullet = true);
    QVector3D getLocation();
    void addHitBox(HitBox* hitbox);
    QVector<HitBox*> hitboxes;
    bool getIsBullet() const;
};

#endif // BULLET_H
