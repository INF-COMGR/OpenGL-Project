#ifndef RENDERER_H
#define RENDERER_H
#include "shaderstatic.h"
#include "entity.h"
#include <QMatrix4x4>

class Renderer
{
public:
    Renderer();
    void renderEntity(Entity entity, ShaderStatic shader);
    QMatrix4x4 createTransformationMatrix(QVector3D translation, float rx, float ry, float rz, float scale);
    void render(QVector<float> vertices);
};

#endif // RENDERER_H
