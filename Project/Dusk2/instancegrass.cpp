#include "instancegrass.h"
#include "util.h"
#include <QOpenGLShaderProgram>
#include <QTextStream>
//#include <QtOpenGLExtensions/QOpenGLExtensions>
//#include <QOpenGLExtensions>

#include "Vertex.h"
/**/
// Create a colored triangle
static const Vertex sg_vertexes[] = {
  Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
  Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
  Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};

/**
 * Proberen aan instancing te doen, maar werd niet door onze openGL ondersteund.
 * Onze ondersteunde openGL was namelijk openGL 2.1 (dit had te maken met ons MacOS systeem)
 * Toen we dit ondervonden, zaten we al te ver in het project en was het niet meer mogelijk nog alles
 * om te gaan zetten naar de nieuwe versie (in dan ook een andere taal).
 *
 * Het omzetten naar de ondersteunde openGL 4.1 werkte ook niet, al ons werk zou dan voor niks geweest zijn.
 *
 * Shaders gaan dus ook maar tot versie 1.2 en voor het gebruik van de 'gl_InstanceID' heb je minimaal 1.4 nodig.
 * We weten wel hoe instancing te werk gaat, maar konden het in ons spel niet implementeren.
 *
 */
InstanceGrass::InstanceGrass()
{
   // QTextStream out(stdout);
    const GLubyte* temp =  glGetString(GL_VERSION);
    const GLubyte* temp2 =  glGetString(GL_SHADING_LANGUAGE_VERSION);

    // Create Shader (Do not release until VAO is created)
     m_program = new QOpenGLShaderProgram();

     m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
            "#version 150 core"

            "in vec3 position;"
            "out vec3 color;"

            "uniform mat4 transformationMatrix;"
            "uniform mat4 projectionMatrix;"
            "uniform float offsets[200];"

           "void main()"
           " {"
             "  vec2 offset = vec2(offsets[gl_InstanceID], offsets[gl_InstanceID + 1]);"
            "   gl_Position = vec4(position.x + offset.x, position.y + offset.y, 0.0, 1.0);"
            "   color = vec3(position.x +offset.x, 1.0, position.y +offset.y);"
           " }"
    );
     m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,                       
           "#version 150 core"

           "in vec3 color;"
           "out vec4 out_Color;"
           "uniform vec3 lightColor;"

           "void main(void)  {"
              "out_Color = vec4(color, 1.0);"
           "}"

     );
     m_program->link();
     m_program->bind();

     float translations[200];
     int index = 0;
     float offset = 0.1f;
     for(int y = -10; y < 10; y += 2)
     {
         for(int x = -10; x < 10; x += 2)
         {
             translations[index++] = (float)x / 10.0f + offset;
             translations[index++] = (float)y / 10.0f + offset;
         }
     }

     // Create Buffer (Do not release until VAO is created)
     m_vertex.create();
     m_vertex.bind();
     m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
     m_vertex.allocate(sg_vertexes, sizeof(sg_vertexes));

     int color_pos = m_program->uniformLocation("color");
     int translations_pos = m_program->uniformLocation("offsets");


     m_program->setUniformValue(color_pos,QVector4D{0.0, 1.0, 0.0, 1.0});
     m_program->setUniformValueArray(translations_pos, translations, 200, 1);

     // Create Vertex Array Object
     m_object.create();
     m_object.bind();
     m_program->enableAttributeArray(0);
     //m_program->enableAttributeArray(1);
     m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
     //m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

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

          glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(sg_vertexes) / sizeof(sg_vertexes[0]), 100);
          m_object.release();
        }
        m_program->release();
    glPopMatrix();

}
