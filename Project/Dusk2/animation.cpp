#include "animation.h"

Animation::Animation(int size, QVector3D location, QString name, int frameAmount, int waitTime):
    size{size}, location{location}, name{name}, FRAME_AMOUNT{frameAmount-1}, WAIT_TIME{waitTime}
{
    initTextures();
}

void Animation::initTextures() {
    for (int i = 0; i < FRAME_AMOUNT; ++i) {
        fireTextures.append(new Texture(name+QString::number(i)+".png"));
    }
}

void Animation::goNextTexture() {
    currentTexture += 1;
    currentTexture %= FRAME_AMOUNT;
}

void Animation::suggestNext() {
    timePassed++;
    if (timePassed >= WAIT_TIME) {
        goNextTexture();
        timePassed = 0;
    }
}

Texture* Animation::getTexture() {
    return fireTextures[currentTexture];
}

void Animation::setSize(int size) {
    this->size = size;
}

void Animation::setLocation(QVector3D location) {
    this->location = location;
}

int Animation::getSize() {
    return size;
}

QVector3D Animation::getLocation() {
    return location;
}
