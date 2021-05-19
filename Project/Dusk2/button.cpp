#include "button.h"
#include "util.h"
#include "Vertex.h"

// Create a colored square
static const Vertex sg_vertexes[] = {
  Vertex( QVector3D( -0.5f,  0.5f, 1.0f)),
  Vertex( QVector3D( 0.5f, -0.5f, 1.0f) ),
  Vertex( QVector3D(-0.5f, -0.5f, 1.0f) ),

    Vertex( QVector3D(-0.5f, 0.5f, 1.0f) ),
    Vertex( QVector3D(0.5f, -0.5f, 1.0f) ),
    Vertex( QVector3D(0.5f, 0.5f, 1.0f) )

};

button::button(QVector4D color, float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    // Create Shader (Do not release until VAO is created)
     m_program = new QOpenGLShaderProgram();
     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
            "varying vec3 position;"
            "uniform vec4 color;"
            "varying vec4 out_Color;"
           "void main()"
           " {"
             "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
            "   out_Color = color;"
           " }"
    );
     m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
            "varying vec3 position;"
            "varying vec4 out_Color;"
            " void main()"
            "{"
              "  gl_FragColor = vec4(out_Color);"
            "}"
     );
     m_program->link();
     m_program->bind();


     // Create Buffer (Do not release until VAO is created)
     m_vertex.create();
     m_vertex.bind();
     m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
     m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

     int color_pos = m_program->uniformLocation("color");
     m_program->setUniformValue(color_pos, color);

     // Create Vertex Array Object
     m_object.create();
     m_object.bind();
     m_program->enableAttributeArray(0);
     m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());

     // Release (unbind) all
     m_object.release();
     m_vertex.release();
     m_program->release();

}

void button::draw(bool isWireframe) {
    glPushMatrix();
        glTranslated(this->x,this->y, this->z);
        // Render using our shader
        m_program->bind();
        {
          m_object.bind();
          glDrawArrays((isWireframe)? GL_LINE_LOOP : GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
          glPushMatrix();
            glTranslated(0, 0, -1);
            glDrawArrays((isWireframe)? GL_LINE_LOOP: GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
          glPopMatrix();
          glPushMatrix();
              glTranslated(-0.5,0,+0.5);
              glRotated(90, 0,1,0);
              glDrawArrays((isWireframe)? GL_LINE_LOOP: GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
              glTranslated(0, 0, -1);
              glDrawArrays((isWireframe)? GL_LINE_LOOP: GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
          glPopMatrix();
          glPushMatrix();
            glRotated(90, 10 ,0 ,0);
            glTranslated(0,+0.5,-1.5);
            glDrawArrays((isWireframe)? GL_LINE_LOOP: GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));
            glTranslated(0,0, +1);
            glDrawArrays((isWireframe)? GL_LINE_LOOP: GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]));

          glPopMatrix();


          m_object.release();
        }
        m_program->release();
    glPopMatrix();


}
