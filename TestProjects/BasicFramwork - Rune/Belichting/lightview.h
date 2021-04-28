#ifndef LIGHTVIEW_H
#define LIGHTVIEW_H
#include "light.h"
#include <QKeyEvent>
class LightView
{
public:
    LightView(float posX, float posY, float posZ, float pos, float diff1, float diff2, float diff3, float diff4);
    void Draw(unsigned long lighting, unsigned long light, unsigned long position, unsigned long diffusion);
    void LightUpdate(QKeyEvent* e);

private:
    Light* light;
};

#endif // LIGHTVIEW_H
