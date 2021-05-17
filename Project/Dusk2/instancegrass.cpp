#include "instancegrass.h"
#include "util.h"
#include <QOpenGLShaderProgram>
#include <QTextStream>

InstanceGrass::InstanceGrass()
{
    float quadVertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };
    test1();
}

void InstanceGrass::test1() {
    QTextStream out(stdout);
    const GLubyte* temp = glGetString(GL_VERSION);
    const GLubyte* temp2 = glGetString( GL_SHADING_LANGUAGE_VERSION );
    QOpenGLShaderProgram program(this);
    program.addShaderFromSourceCode(QOpenGLShader::Vertex,
        "attribute highp vec4 vertex;\n"
        "uniform highp mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "   gl_Vertex.x += gl_InstanceID;\n"
        "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
        "}");
    program.addShaderFromSourceCode(QOpenGLShader::Fragment,
        "uniform mediump vec4 color;\n"
        "void main(void)\n"
        "{\n"
        "   gl_FragColor = color;\n"
        "}");

    program.link();
    program.bind();

    QMatrix4x4 pmvMatrix;
    pmvMatrix.ortho(rect());


    int vertexLocation = program.attributeLocation("vertex");
    int matrixLocation = program.uniformLocation("matrix");
    int colorLocation = program.uniformLocation("color");
    static GLfloat const triangleVertices[] = {
        0.0f,  0.0f,  2.0f,
        10.0f, 10.0f, 2.0f,
        5.0f,  10.0f, 2.0f
    };

    QColor color(255, 0, 0, 255);

    program.enableAttributeArray(vertexLocation);
    program.setAttributeArray(vertexLocation, triangleVertices, 3);
    program.setUniformValue(matrixLocation, pmvMatrix);
    program.setUniformValue(colorLocation, color);

    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 30);

    program.disableAttributeArray(vertexLocation);
    program.release();
}

//void InstanceGrass::test() {
//    static GLfloat wall [] = {
//            (float) x1, (float) y1, (float) z1,
//            (float) x2, (float) y2, (float) z2,
//            (float) x3, (float) y3, (float) z3,
//            (float) x4, (float) y4, (float) z4
//        };

//        static GLfloat color [] = {
//            1.0f, 0.0f, 0.0f, 1.0f
//        };

//        static GLfloat texCoords [] {
//            1.0f, 1.0f,
//            1.0f, 0.0f,
//            0.0f, 0.0f,
//             0.0f, 1.0f

//        };
//        QOpenGLTexture* m_texture = new QOpenGLTexture( QImage( QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg") );
//        QOpenGLShaderProgram program(this);

//        program.addShaderFromSourceCode(QOpenGLShader::Vertex,
//            "attribute highp vec4 vertex;\n"
//            "attribute highp vec4 texCoord;\n"
//            "uniform mediump mat4 matrix;\n"
//            "varying highp vec4 texc;\n"

//            "void main(void)\n"
//            "{\n"
//                "gl_Position = ftransform();"
//                "texc = texCoord;"
//            "}");

//        program.addShaderFromSourceCode(QOpenGLShader::Fragment,
//            "varying highp vec4 texc;\n"
//            "uniform sampler2D tex;\n"

//            "void main(void)\n"
//            "{\n"
//            "   highp vec3 color = texture2D( tex, texc.st ).rgb;\n"
//            "   color = color * 0.2 + color * 0.8;\n"
//            "   gl_FragColor = vec4( clamp( color, 0.0, 1.0 ), 1.0 );\n"
//            "}");

//        program.link();
//        program.bind();

//        int vertexLocation = program.attributeLocation("vertex");
//        int textCoord = program.uniformLocation("texCoord");
//        int textUniform = program.uniformLocation("tex");

//        addTexture();
//        program.setAttributeArray(vertexLocation, wall, 3);
//        program.setAttributeArray(textCoord, texCoords, 2);
//        program.setUniformValue(textUniform, 0);

//        program.enableAttributeArray(vertexLocation);
//        program.enableAttributeArray(textCoord);

//        glDrawArrays(GL_QUADS, 0, 4);
//        program.disableAttributeArray(vertexLocation);
//        program.disableAttributeArray(textCoord);

//        program.release();

//}
