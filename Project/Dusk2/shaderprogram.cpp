#include "shaderprogram.h"
#include <QFile>
#include <QTextStream>

ShaderProgram::ShaderProgram()
{

}

ShaderProgram::ShaderProgram(QString vertexFile, QString fragmentFile) {
       loadShaders(vertexFile.toStdString().c_str(), fragmentFile.toStdString().c_str());
       bindAttributes();
       //glLinkProgram(programID);
       glValidateProgram(programID);
       getAllUniformLocations();
}

void ShaderProgram::checkCompiled(int InfoLogLength)
{
    if ( InfoLogLength > 0 ){
        QTextStream out(stdout);
        QVector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        const GLubyte* test =  glGetString(GL_VERSION);
         const GLubyte* test2 = glGetString(GL_SHADING_LANGUAGE_VERSION);
        out << glGetString(GL_VERSION);
        out << (VertexShaderErrorMessage[0]);
    }
}

void ShaderProgram::loadShaders(const char * vertex_file_path,const char * fragment_file_path) {
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


        const char* VertexSourcePointer = readShaderFile(vertex_file_path);
        const char* FragmentSourcePointer = readShaderFile(fragment_file_path);


        GLint Result = GL_FALSE;
        int InfoLogLength;


        glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(vertexShaderID);
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

        checkCompiled(InfoLogLength);



        glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(fragmentShaderID);

        glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

        checkCompiled(InfoLogLength);


    programID = glCreateProgram();

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);

    glLinkProgram(programID);
    glValidateProgram(programID);
    glUseProgram(programID);


}

const char * ShaderProgram::readShaderFile(const char * file_path) {
    QFile file(file_path);
    QString fileToText = "";
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return "";

    QTextStream in(&file);

    while (!in.atEnd()) {
           QString line = in.readLine();
           fileToText.append(line).append("//\n");
     }

   QByteArray temp = fileToText.toUtf8();
   return temp.constData();

}

void ShaderProgram::bindAttribute(int attribute, const char* variableName){
    glBindAttribLocation(programID, attribute, variableName);
}

GLuint ShaderProgram::getProgramID() const
{
    return programID;
}

void ShaderProgram::setProgramID(const GLuint &value)
{
    programID = value;
}

void ShaderProgram::stop() {
    glUseProgram(0);

}

void ShaderProgram::start() {
    glUseProgram(programID);
}


void ShaderProgram::getAllUniformLocations() {

}
void ShaderProgram::bindAttributes() {

}

void ShaderProgram::cleanUp(){
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

int ShaderProgram::getUniformLocation(QString uniformName) {
       QByteArray temp = uniformName.toUtf8();
       return glGetUniformLocation(programID, temp.constData());
}
