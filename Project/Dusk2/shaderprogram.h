#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include "util.h"
#include <QString>
#include <QMatrix4x4>

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(QString vertexFile, QString fragmentFile);
    void loadShaders(const char * vertex_file_path,const char * fragment_file_path);
    void stop();
    void cleanUp();
    void start();
    int getUniformLocation(QString uniformName);
    const char* readShaderFile(const char * file_path);


    virtual void getAllUniformLocations();
    virtual void bindAttributes();
    void bindAttribute(int attribute, const char*);

    GLuint getProgramID() const;
    void setProgramID(const GLuint &value);

private:
    GLuint vertexShaderID, fragmentShaderID, programID;
    void checkCompiled(int InfoLogLength);
};

#endif // SHADERPROGRAM_H
