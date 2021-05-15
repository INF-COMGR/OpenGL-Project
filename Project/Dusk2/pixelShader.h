#ifndef PIXELSHADER_H
#define PIXELSHADER_H
#include <QVector4D>
#include <QVector3D>

class PixelShader
{
public:
    PixelShader();
private:
    float precision;
    QVector3D eye_LightPos;
    QVector3D pixel_LightPos;
    QVector4D pixel_Color;
    QVector3D normal;

};

#endif // PIXELSHADER_H

