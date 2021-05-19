#ifndef ANIMATION_H
#define ANIMATION_H
#include <QVector3D>
#include <QVector>
#include <QString>
#include "texture.h"

class Animation
{
private:
    int size;
    QVector3D location;
    QVector<Texture*> fireTextures = QVector<Texture*>{};
    void initTextures();
    int currentTexture = 0;
    void goNextTexture();

    const QString name;
    const int FRAME_AMOUNT;
    const int WAIT_TIME;

    int timePassed = 0;
public:
    Animation(int size, QVector3D locaton, QString name, int frameAmount, int waitTime);
    int getSize();
    QVector3D getLocation();
    void setSize(int size);
    void setLocation(QVector3D location);
    void suggestNext();

    Texture* getTexture();
};

#endif // ANIMATION_H
