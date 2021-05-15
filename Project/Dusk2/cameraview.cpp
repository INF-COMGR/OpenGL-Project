#include "cameraview.h"
#include "util.h"
#include <QVector2D>
#include <QVector3D>
CameraView::CameraView()  {
    camera = new Camera();
}

QVector3D CameraView::getCameraLocation() {
    return camera->getLocation();
}
QVector3D CameraView::getCameraLookingDirection() {
    return camera->getViewVector();
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
    if (e->key() == Qt::Key_F)
        camera->toggleFlying();

    if (!camera->isFlying()) {
        if(e->key() == Qt::Key_Z)
            camera->walkForward();

        if(e->key() == Qt::Key_S)
            camera->walkBackward();

        if(e->key() == Qt::Key_Q)
            camera->walkLeft();

        if(e->key() == Qt::Key_D)
            camera->walkRight();
    }
    else {
        if(e->key() == Qt::Key_Z)
            camera->flyForward();

        if(e->key() == Qt::Key_S)
            camera->flyBackward();

        if(e->key() == Qt::Key_Q)
            camera->flyLeft();

        if(e->key() == Qt::Key_D)
            camera->flyRight();
    }

}

void CameraView::mouseMouveEvent(QMouseEvent* e) {
    QVector2D mouse = {(float) e->x(), (float) e->y()};
    camera->mouseUpdate(mouse);
}
