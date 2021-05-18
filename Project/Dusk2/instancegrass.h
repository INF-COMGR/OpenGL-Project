#ifndef INSTANCEGRASS_H
#define INSTANCEGRASS_H
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class QOpenGLShaderProgram;

class InstanceGrass : public QOpenGLWidget
{
public:
    InstanceGrass();
    void draw();
    // OpenGL State Information
     QOpenGLBuffer m_vertex;
     QOpenGLVertexArrayObject m_object;
     QOpenGLShaderProgram *m_program;
};

#endif // INSTANCEGRASS_H
