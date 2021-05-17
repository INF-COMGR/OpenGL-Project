#ifndef LOADER_H
#define LOADER_H
#include <QList>
#include "util.h"
class RawModel;

class Loader
{
public:
    Loader();
    void cleanUp();
    RawModel* loadToVAO(float* positions, int* indices,int mode);
    GLuint createVAO();

    void storeDataInAttributeList(int attributeNumber,int coordinateSize, float* data);
    void unBindVao();
    void bindIndicesBuffer(int* indices);
    int* storeDataInIntBuffer(int* data);
    float* storeDataInFloatBuffer(float* data);

private:
    GLuint* vaos = new GLuint[100];
    GLuint* vbos = new GLuint[100];
    int vaosSize = 0;
    int vbosSize = 0;
};

#endif // LOADER_H
