#ifndef PICKING_H
#define PICKING_H
#include <OpenGL/gl.h>
class Camera;

class picking
{
private:
    const static int buffSize = 512;
    GLuint selectBuff[buffSize];
public:
    picking();
    int pick(Camera* camera);
};

#endif // PICKING_H
