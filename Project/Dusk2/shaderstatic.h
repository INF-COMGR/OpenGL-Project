#ifndef SHADERSTATIC_H
#define SHADERSTATIC_H

#include "shaderprogram.h"
#include <QCoreApplication>


class ShaderStatic : public ShaderProgram
{
public:
    ShaderStatic();
    //void loadMatrix(int location, QMatrix4x4 matrix);


    void getAllUniformLocations();
    void bindAttributes();
    void setColor(QVector4D color);
    int getTexture_location() const;

    int getColor_location() const;

private:
    QString VERTEX_FILE{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/vertexShader.txt"};
    QString FRAGMENT_FILE{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/fragmentShader.txt"};
    int texture_location;
    int color_location;
};

#endif // SHADERSTATIC_H
