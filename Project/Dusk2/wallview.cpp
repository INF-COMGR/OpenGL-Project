#include "wallview.h"
#include "util.h"
#include "math.h"
//#include <QTextStream>
#include <QCoreApplication>

//#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

WallView::WallView(double x1, double y1, double z1, double x2, double y2, double z2, float red, float green, float blue)
{
    this->wall = new Wall(x1, y1, z1, x2, y2, z2);
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->bottomLeft = *wall->getBottomLeft();
    this->bottomRight = *wall->getBottomRight();
    this->topRight = *wall->getTopRight();
    this->topLeft = *wall->getTopLeft();
}

WallView::WallView(Wall* wall, float red, float green, float blue) {
    this->wall = wall;
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->bottomLeft = *wall->getBottomLeft();
    this->bottomRight = *wall->getBottomRight();
    this->topRight = *wall->getTopRight();
    this->topLeft = *wall->getTopLeft();
}

void WallView::draw(bool isWireframe) {
    double x1 = bottomLeft[0];
    double y1 = bottomLeft[1];
    double z1 = bottomLeft[2];

    double x2 = bottomRight[0];
    double y2 = bottomRight[1];
    double z2 = bottomRight[2];

    double x3 = topRight[0];
    double y3 = topRight[1];
    double z3 = topRight[2];

    double x4 = topLeft[0];
    double y4 = topLeft[1];
    double z4 = topLeft[2];

    if (!isWireframe)
        addTexture();

//    glColor4f((blue)/255.0f,
//              (green)/255.0f,
//              (blue)/255.0f,
//              1.0f);
    float mcolor[] = { blue/255.0f, (green)/255.0f, (blue)/255.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

    glEnable(GL_NORMALIZE);
//    QVector3D normal = getNormal(bottomLeft, bottomRight, topRight);
//    glNormal3f(normal[0], normal[1], normal[2]);
    glBegin(!isWireframe ? GL_QUADS : GL_LINE_LOOP);
        //glNormal3f(1.0, 1.0, 1.0);
        glTexCoord2d( 0.0, 5.0 );
        glVertex3f(x1,y1,z1);
        glTexCoord2d( 0.0, 0.0 );
        glVertex3f(x2,y2,z2);
        glTexCoord2d( 2.5, 0.0 );
        glVertex3f(x3,y3,z3);
        glTexCoord2d( 2.5, 5.0);
        glVertex3f(x4,y4,z4);
    glEnd();
//    glColor4f(1, 1, 1, 1);
}

void WallView::addTexture() {
    unsigned int texture;
    int width, height, nrChannels;

    QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
    //std::cout << " " << path.toStdString() << " ";
    unsigned char *image = stbi_load(path.toStdString().c_str(), &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (image != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    }
    else {
        perror( stbi_failure_reason() );
    }
    stbi_image_free(image);


    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    // use our previously defined texture
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D , texture );

}

QVector3D WallView::getNormal(QVector3D a, QVector3D b, QVector3D c) {

    QVector3D x = b - a;
    QVector3D y = c - a;
    QVector3D normal = QVector3D::crossProduct(x, y);
    normal = normalize(normal);
    return normal;


}

QVector3D WallView::normalize(QVector3D a) {
    float sum = (a[0])*(a[0]) + (a[1])*(a[1]) + (a[2])*(a[2]);
    float length = (float) sqrt( (double) sum);
    for (int i = 0; i < 3; ++ i) {
        a[i] = a[i] / length;
    }
    return a;
}
//// This is how a vertex is specified in the base code
//    typedef struct vertex_s
//    {
//    float x, y, z;
//    } vertex_t;

//    // normal(); - finds a normal vector and normalizes it
//    void normal (vertex_t v[3], vertex_t *normal)
//    {
//    vertex_t a, b;

//    // calculate the vectors A and B
//    // note that v[3] is defined with counterclockwise winding in mind
//    // a
//    a.x = v[0].x - v[1].x;
//    a.y = v[0].y - v[1].y;
//    a.z = v[0].z - v[1].z;
//    // b
//    b.x = v[1].x - v[2].x;
//    b.y = v[1].y - v[2].y;
//    b.z = v[1].z - v[2].z;

//    // calculate the cross product and place the resulting vector
//    // into the address specified by vertex_t *normal
//    normal->x = (a.y * b.z) - (a.z * b.y);
//    normal->y = (a.z * b.x) - (a.x * b.z);
//    normal->z = (a.x * b.y) - (a.y * b.x);

//    // normalize
//    normalize(normal);
//    }

