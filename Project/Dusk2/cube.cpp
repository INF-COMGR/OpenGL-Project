#include "cube.h"
#include "util.h"
#include "texture.h"
Cube::Cube(double x1, double y1, double z1, double x2, double y2, double z2)
{
    this->x1 = x1;
    this->y1 = y1;
    this->z1 = z1;
    this->x2 = x2;
    this->y2 = y2;
    this->z2 = z2;
    this->texture = new Texture("littleWall2.jpg");

}

void Cube::draw(bool isWireframe) {
    //float mcolor[] = { blue/255.0f, (green)/255.0f, (blue)/255.0f, 1.0f };
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

    glEnable(GL_NORMALIZE);
    texture->bindTexture();
    glBegin(!isWireframe ? GL_QUADS : GL_LINE_LOOP);
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z1);

        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y1,z1);

        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x2,y2,z1);

        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x1,y2,z1);
   //-------------------------------

        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z1);

        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x1,y2,z1);

        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x1,y2,z2);

        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x1,y1, z2);
    //-----------------------------
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z2);

        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x1,y2,z2);

        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x2,y2,z2);

        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x2,y1, z2);

        //-----------------------------
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x2,y1,z2);

        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y2,z2);

        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x2,y2,z1);

        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x2,y1, z1);

        //-----------------------------

        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y2,z1);

        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y2,z1);

        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x2,y2,z2);

        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x1,y2, z2);

    glEnd();
    texture->unBindTexture();
}
