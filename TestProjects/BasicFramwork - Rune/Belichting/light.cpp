#include "light.h"

Light::Light(float posX, float posY, float posZ, float pos, float diff1, float diff2, float diff3, float diff4) {
    position = {posX, posY, posZ, pos};
    diffusion = {diff1, diff2, diff3, diff4};

}

QVector<float> Light::getPosition()  {
    return position;
}
QVector<float> Light::getDiffusion() {
    return diffusion;
}

void Light::moveForward(float x, float y, float z) {
    position[0] += speed * x;
    position[1] += speed * y;
    position[2] += speed * z;
}

void Light::moveBackward(float x, float y, float z) {
    position[0] += -speed * x;
    position[1] += -speed * y;
    position[2] += -speed * z;
}
