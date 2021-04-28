#ifndef GLOBEVIEW_H
#define GLOBEVIEW_H
#include "globe.h"


class GlobeView
{
public:
    GlobeView(float radius, float red, float yellow, float blue);
    void Draw(unsigned long shading,unsigned long material, unsigned long mode1);
private:
    Globe* globe;

};

#endif // GLOBEVIEW_H
