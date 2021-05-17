#ifndef RAWMODEL_H
#define RAWMODEL_H
#include "util.h"

class RawModel
{
public:
    RawModel();
    RawModel(GLuint vaoID, int vertexCount, GLenum mode);
    int getVaoID();

    int getVertexCount();

    int getMode();
private:
    GLuint vaoID;
    int vertexCount;
    GLenum mode;
};

#endif // RAWMODEL_H
