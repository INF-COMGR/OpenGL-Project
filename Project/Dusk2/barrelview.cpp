#include "barrelview.h"
#include "barrel.h"
#include "util.h"
#define STB_IMAGE_IMPLEMENTATION

BarrelView::BarrelView(int size, QVector3D location)
{
    barrel = new Barrel(size, location);
}

void BarrelView::draw(bool isWireframe)
{
    glPushMatrix();
    float size = (float)barrel->getSize();
    float alpha = size/4.0f;
    float beta = sqrt(3) * alpha;

    QVector3D location = barrel->getLocation();
    glTranslated(location.x(), location.y(), location.z());

    float mcolor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
    glEnable(GL_NORMALIZE);
    // BOTTEM
//    QVector3D normal1 = getNormal(QVector3D{beta, 0, alpha}, QVector3D{beta, 0, -alpha},QVector3D{0, 0, -2 * alpha});
//    glNormal3f(normal1[0], normal1[1], normal1[2]);
    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
        glVertex3d(0, 0, -2 * alpha);
        glVertex3d(beta, 0, -alpha);
        glVertex3d(beta, 0, alpha);
        glVertex3d(0, 0, 2 * alpha);
        glVertex3d(-beta, 0, alpha);
        glVertex3d(-beta, 0, -alpha);
    glEnd();

    // BODY
    glBegin( !isWireframe ? GL_QUAD_STRIP : GL_LINE_LOOP );
//        QVector3D normal1 = getNormal(QVector3D{beta, 0, alpha}, QVector3D{beta, 0, -alpha},QVector3D{0, 0, -2 * alpha});
//        glNormal3f(normal1[0], normal1[1], normal1[2]);
        glVertex3d(0, 0, -2 * alpha);
        glVertex3d(0, size, -2 * alpha);
        glVertex3d(beta, 0, -alpha);
        glVertex3d(beta, size, -alpha);

        glVertex3d(beta, 0, alpha);
        glVertex3d(beta, size, alpha);

        glVertex3d(0, 0, 2 * alpha);
        glVertex3d(0, size, 2 * alpha);

        glVertex3d(-beta, 0, alpha);
        glVertex3d(-beta, size, alpha);

        glVertex3d(-beta, 0, -alpha);
        glVertex3d(-beta, size, -alpha);

        glVertex3d(0, 0, -2 * alpha);
        glVertex3d(0, size, -2 * alpha);
    glEnd();

    // TOP

//    QVector3D normal6 = getNormal(QVector3D{beta, size, alpha}, QVector3D{beta, size, -alpha},QVector3D{0, size, -2*alpha});
//    glNormal3f(normal6[0], normal6[1], normal6[2]);
    glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
        glVertex3d(0, size, -2 * alpha);
        glVertex3d(beta, size, -alpha);
        glVertex3d(beta, size, alpha);
        glVertex3d(0, size, 2 * alpha);
        glVertex3d(-beta, size, alpha);
        glVertex3d(-beta, size, -alpha);
    glEnd();

    glPopMatrix();
}

void BarrelView::getTexture() {
    /*int imageWidth = 0;
    int imageHeight = 0;
    unsigned char* image = SOIL_load_image*/
}

QVector3D BarrelView::getNormal(QVector3D a, QVector3D b, QVector3D c) {

    QVector3D x = b - a;
    QVector3D y = c - a;
    QVector3D normal = QVector3D::crossProduct(x, y);
    normal = normalize(normal);
    return normal;


}

QVector3D BarrelView::normalize(QVector3D a) {
    float sum = (a[0])*(a[0]) + (a[1])*(a[1]) + (a[2])*(a[2]);
    float length = (float) sqrt( (double) sum);
    for (int i = 0; i < 3; ++ i) {
        a[i] = a[i] / length;
    }
    return a;
}
