#include "picking.h"
#include <GLUT/glut.h>
#include "camera.h"

picking::picking()
{
}

int picking::pick(Camera* camera)
{
    glSelectBuffer(buffSize, selectBuff);
    glRenderMode( GL_SELECT );
    glInitNames();

    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );

    GLdouble pm[16];
    glGetDoublev( GL_PROJECTION_MATRIX, pm );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
        //glLoadIdentity();
        gluLookAt(camera->getPosX(), camera->getPosY(), camera->getPosZ(), camera->getPosX() + camera->getViewX(),  camera->getPosY() + camera->getViewY(), camera->getPosZ() + camera->getViewZ(), camera->getUpX(), camera->getUpY(), camera->getUpZ());
        gluPickMatrix( 10, (viewport[3] - 10), 5.0, 5.0, viewport);
        glMultMatrixd( pm );


        glPushName(1);
        glBegin( GL_TRIANGLES );
            glVertex3d(-10, -10, -5);
            glVertex3d(30, 5, 5);
            glVertex3d(5, 30, 5);
        glEnd();
        glPopName();

   glMatrixMode( GL_PROJECTION );
   glPopMatrix();

   GLint hits = glRenderMode( GL_RENDER );

   GLuint minMinZ = 0xffffffff;

   int firstHit = -1;
   GLuint *ptr = (GLuint*) selectBuff;
   for (GLint i = 0; i < hits; ++i) {
       GLuint nrNames = *ptr;
       ptr++;
       GLuint minZ = *ptr;
       ptr++;
       GLuint maxZ = *ptr;
       ptr++;
       for (GLuint j = 0; j < nrNames; ++j) {
           if (minZ < minMinZ) {
               minMinZ = minZ;
               firstHit = *ptr;
           }
           ptr++;
       }
   }

   return firstHit;

}
