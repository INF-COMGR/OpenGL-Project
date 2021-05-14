#include "camera.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>

Camera::Camera()
{
    camPosx = 3.0f,  camPosy = cameraHeight,    camPosz = 25.0f;
    camViewx = 0.0f, camViewy = 0.0f, camViewz = -1.0f;
    camUpx = 0.0f,   camUpy = 1.0f,   camUpz = 0.0f;

    flying = false;
}

void Camera::mouseUpdate(const QVector2D& newMousePosition) {
    QVector2D mouseDelta = newMousePosition - oldMousePosition;

    QMatrix4x4 horizontalMatrix;
    QVector3D viewDirection = {camViewx, camViewy, camViewz};

    horizontalMatrix.rotate(-mouseDelta.x(), camUpx, camUpy, camUpz);

    viewDirection = horizontalMatrix * viewDirection;

    camViewx = viewDirection.x();
    camViewy = viewDirection.y();
    camViewz = viewDirection.z();

    QMatrix4x4 verticalMatrix;
    QVector3D strafe = getStrafe();

    verticalMatrix.rotate(-mouseDelta.y(), strafe);    //rotate around Strafe Vector
    viewDirection = verticalMatrix * viewDirection;

    camViewx = viewDirection.x();
    camViewy = viewDirection.y();
    camViewz = viewDirection.z();

    QRect rec = QApplication::desktop()->screenGeometry();
    oldMousePosition = {(float)rec.width()/2, (float)rec.height()/2};
    QCursor::setPos(rec.width()/2, rec.height()/2);
}

QVector3D Camera::getStrafe() {
    QVector3D View = {camViewx, camViewy, camViewz};
    QVector3D UP = {camUpx, camUpy, camUpz};
    return (QVector3D::crossProduct(View, UP));
}


void Camera::walkForward() {
    camPosx += speed * camViewx;
    camPosy = cameraHeight;
    camPosz += speed * camViewz;
}

void Camera::walkBackward() {
    camPosx += -speed * camViewx;
    camPosy = cameraHeight;
    camPosz += -speed * camViewz;
}

void Camera::walkLeft() {
    QVector3D strafe = getStrafe();
    camPosx += -speed * strafe.x();
    camPosy = cameraHeight;
    camPosz += -speed * strafe.z();

}
void Camera::walkRight() {
    QVector3D strafe = getStrafe();
    camPosx += speed * strafe.x();
    camPosy = cameraHeight;
    camPosz += speed * strafe.z();

}

void Camera::flyForward() {
    camPosx += speed * camViewx;
    camPosy += speed * camViewy;
    camPosz += speed * camViewz;
}

void Camera::flyBackward() {
    camPosx += -speed * camViewx;
    camPosy += -speed * camViewy;
    camPosz += -speed * camViewz;
}

void Camera::flyLeft() {
    QVector3D strafe = getStrafe();
    camPosx += -speed * strafe.x();
    camPosy += speed * strafe.y();
    camPosz += -speed * strafe.z();

}
void Camera::flyRight() {
    QVector3D strafe = getStrafe();
    camPosx += speed * strafe.x();
    camPosy += speed * strafe.y();
    camPosz += speed * strafe.z();

}

bool Camera::isFlying() {
    return flying;
}

void Camera::toggleFlying() {
    flying = !flying;
}

double Camera::getPosX() {
    return camPosx;
}
double Camera::getPosY() {
    return camPosy;
}
double Camera::getPosZ() {
    return camPosz;
}
double Camera::getViewX() {
    return camViewx;
}
double Camera::getViewY() {
    return camViewy;
}
double Camera::getViewZ() {
    return camViewz;
}
double Camera::getUpX() {
    return camUpx;
}
double Camera::getUpY() {
    return camUpy;
}
double Camera::getUpZ() {
    return camUpz;
}



