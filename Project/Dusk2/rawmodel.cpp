#include "rawmodel.h"

RawModel::RawModel() {}
RawModel::RawModel(GLuint vaoID, int vertexCount, GLenum mode)
{
    this->vaoID = vaoID;
    this->vertexCount = vertexCount;
    this->mode = mode;
}

int RawModel::getVaoID() {
       return this->vaoID;
   }

int RawModel::getVertexCount() {
       return this->vertexCount;
   }

int RawModel::getMode() {
       return this->mode;
   }
