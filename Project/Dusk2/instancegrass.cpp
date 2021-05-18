#include "instancegrass.h"
#include "util.h"
#include <QOpenGLShaderProgram>
#include <QTextStream>
//#include <QtOpenGLExtensions/QOpenGLExtensions>
//#include <QOpenGLExtensions>

#include "vertex.h"

// Create a colored triangle
static const Vertex sg_vertexes[] = {
  Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
  Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
  Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};

InstanceGrass::InstanceGrass()
{
   // QTextStream out(stdout);
    const GLubyte* temp =  glGetString(GL_VERSION);
    const GLubyte* temp2 =  glGetString(GL_SHADING_LANGUAGE_VERSION);

    // Create Shader (Do not release until VAO is created)
     m_program = new QOpenGLShaderProgram();
     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
            "void main()"
           " {"
             "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
           " }"
    );
     m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,

            " void main()"
            "{"
              "  gl_FragColor = vec4(0.4,0.4,0.8,1.0);"
            "}"
     );
     m_program->link();
     m_program->bind();

     // Create Buffer (Do not release until VAO is created)
     m_vertex.create();
     m_vertex.bind();
     m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
     m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

     // Create Vertex Array Object
     m_object.create();
     m_object.bind();
     m_program->enableAttributeArray(0);
     m_program->enableAttributeArray(1);
     m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
     m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

     // Release (unbind) all
     m_object.release();
     m_vertex.release();
     m_program->release();
}

void InstanceGrass::draw() {
    glPushMatrix();
        glTranslated(2,2,0);
        // Render using our shader
        m_program->bind();
        {
          m_object.bind();

          glDrawArraysInstancedARB(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]), 100);
          m_object.release();
        }
        m_program->release();
    glPopMatrix();

}
