#ifndef LIGHT_H
#define LIGHT_H
#include "util.h"
#include <QVector>

class Light
{
public:
    Light(float posX, float posY, float posZ, float pos, float diff1, float diff2, float diff3, float diff4);
    QVector<float> getPosition();
    QVector<float> getDiffusion();
    void moveForward(float x, float y, float z);
    void moveBackward(float x, float y, float z);

private:
    QVector<float> position;
    QVector<float> diffusion;
    float speed = 0.1f;
//    GLfloat position[];
//    GLfloat diffusion[];

};

#endif // LIGHT_H
