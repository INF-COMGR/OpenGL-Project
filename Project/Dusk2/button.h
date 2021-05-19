#ifndef BUTTON_H
#define BUTTON_H
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class button
{
public:
    button(QVector4D color, float x, float y, float z);
    void draw(bool isWireframe);
private:
    // OpenGL State Information
     QOpenGLBuffer m_vertex;
     QOpenGLVertexArrayObject m_object;
     QOpenGLShaderProgram *m_program;
     float x, y, z;
};

#endif // BUTTON_H
