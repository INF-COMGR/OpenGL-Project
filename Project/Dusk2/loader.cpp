#include "loader.h"
#include "rawmodel.h"
#include "util.h"

Loader::Loader()
{

}
void Loader::cleanUp() {
   for (int i = 0; i < vaosSize; ++i) {
       glDeleteVertexArraysAPPLE(1, &vaos[i]);
   }

   for (int i = 0; i < vbosSize; ++ i) {
       glDeleteBuffers(1, &vbos[i]);
   }


}

RawModel* Loader::loadToVAO(float* positions, int* indices,int mode) {
    GLuint vaoID = createVAO();

    bindIndicesBuffer(indices);
    storeDataInAttributeList(0,3 , positions);
    unBindVao();

    return new RawModel(vaoID, sizeof(indices)/sizeof(int)  /* x,y,z */, mode);
}


GLuint Loader::createVAO() {
    GLuint vaoID;
    glGenVertexArraysAPPLE(1, &vaoID);
    vaos[vaosSize] = vaoID;
    ++vaosSize;
    glBindVertexArrayAPPLE(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber,int coordinateSize, float* data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos[vbosSize] = vboID;
    ++vbosSize;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    float* buffer = storeDataInFloatBuffer(data);

    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0,0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind the current vbo
}

void Loader::unBindVao() {
    glBindVertexArrayAPPLE(0);
}

void Loader::bindIndicesBuffer(int* indices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos[vbosSize] = (vboID);
    ++vbosSize;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    int* buffer = storeDataInIntBuffer(indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1,buffer, GL_STATIC_DRAW);

}

int* Loader::storeDataInIntBuffer(int* data) {
    int buffer[sizeof(data)/sizeof(int)] = {};
    for (int i = 0; i < sizeof(data)/sizeof(int); ++i) {
        buffer[i] = data[i];
    }
    return buffer;
}

float* Loader::storeDataInFloatBuffer(float* data) {
    float buffer[sizeof(data)/sizeof(float)] = {};
    for (int i = 0; i < sizeof(data)/sizeof(float); ++i) {
        buffer[i] = data[i];
    }
    return buffer;
}
