#include "cameraview.h"
#include "util.h"
#include "camera.h"
#include <QMouseEvent>

CameraView::CameraView() {
    camera = new Camera();
}

void CameraView::Draw() {
    gluLookAt(camera->getPosX(), camera->getPosY(), camera->getPosZ(),
              camera->getViewX(), camera->getViewY(), camera->getViewZ(),
              camera->getUpX(), camera->getUpY(), camera->getUpZ());
    if (axisEnabled) {
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
    glEnable(GL_COLOR_MATERIAL);
    }
}

void CameraView::changeCam(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ) {
    camera->changeCam(posX, posY, posZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);
}

void CameraView::toggleFreeCam() {
    camera->toggleFreeCam();
}

void CameraView::keyPressedEvent(QKeyEvent *e) {
    camera->keyUpdate(e);
}

void CameraView::mouseMoveEvent(QMouseEvent *e) {
    camera->mouseUpdate(new QVector2D(e->x(), e->y()));
}

void CameraView::toggleAxis() {
    axisEnabled = axisEnabled ? false : true;
}
