#include "model.h"

Model::Model()
{
    GLfloat test[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    int index = 0;
    for (GLfloat value : test) {
        vertices[index] = value;
        ++index;
    }


}
