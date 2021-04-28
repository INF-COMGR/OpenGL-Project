#include "cameraview.h"
#include "util.h"
#include <QVector2D>
CameraView::CameraView()  {
    camera = new Camera();
}

void CameraView::Draw() {
    gluLookAt( camera->getPosX(), camera->getPosY(), camera->getPosZ(),
               camera->getPosX() + camera->getViewX(),  camera->getPosY() + camera->getViewY(), camera->getPosZ() + camera->getViewZ(),
               camera->getUpX(), camera->getUpY(), camera->getUpZ()
                );

    //Draw Axes
    glDisable( GL_LIGHTING );
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glEnable( GL_LIGHTING );
}

void CameraView::keyPressEvent(QKeyEvent * e) {
    if(e->key() == Qt::Key_Up)
        camera->moveForward();

    if(e->key() == Qt::Key_Down)
        camera->moveBackward();

    if(e->key() == Qt::Key_Left)
        camera->Left();

    if(e->key() == Qt::Key_Right)
        camera->Right();


    if(e->key() == Qt::Key_Z)
        camera->addUpY(0.5);
    if(e->key() == Qt::Key_S)
        camera->addUpY(-0.5);
    if(e->key() == Qt::Key_Q)
        camera->addUpX(-0.5);
    if(e->key() == Qt::Key_D)
        camera->addUpX(0.5);
}

void CameraView::mouseMouveEvent(QMouseEvent* e) {
    QVector2D mouse = {(float) e->x(), (float) e->y()};
    camera->mouseUpdate(mouse);
}
