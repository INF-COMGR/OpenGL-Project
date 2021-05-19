#ifndef ANIMATIONVIEW_H
#define ANIMATIONVIEW_H
#include <QVector>
class Animation;
class QVector3D;
class QVector2D;
class QString;

class AnimationView
{
private:
    Animation* animation;
    QVector<QVector2D> texCoords;
    const float RATIO; //= 1.0f;//16.0f/35.0f;
public:
    AnimationView(int size, QVector3D location, QString name, int frameAmount, QVector<QVector2D> texCoords, float ratio = 1.0f, int waitTime = 1);
    void draw(bool isWireframe = false);
};

#endif // ANIMATIONVIEW_H
