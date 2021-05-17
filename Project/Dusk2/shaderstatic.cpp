#include "shaderstatic.h"


ShaderStatic::ShaderStatic() : ShaderProgram(QCoreApplication::applicationDirPath() + "/../../../../Dusk2/vertexShader.txt", QCoreApplication::applicationDirPath() + "/../../../../Dusk2/fragmentShader.txt") {
    getAllUniformLocations();
}


void ShaderStatic::getAllUniformLocations() {
    texture_location = getUniformLocation("TextureUnit0");
    color_location = getUniformLocation("color");

}
void ShaderStatic::bindAttributes() {
    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
    //this->bindAttribute(0, "TextureUnit0");
}

int ShaderStatic::getTexture_location() const
{
    return texture_location;
}

int ShaderStatic::getColor_location() const
{
    return color_location;
}

void ShaderStatic::setColor(QVector4D color) {
    float colorFloats[4];
    for (int i = 0; i < 4; ++i) {
        colorFloats[i] = color[i];
    }
    glUniform1fv(color_location, 4,colorFloats);
}


