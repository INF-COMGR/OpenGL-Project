#include "camera.h"
#include <QVector3D>
#include <QMatrix4x4>

Camera::Camera()
{
    camPosx = 3.0f,  camPosy = 5.0f,    camPosz = 25.0f;
    camViewx = 0.0f, camViewy = 0.0f, camViewz = -1.0f;
    camUpx = 0.0f,   camUpy = 1.0f,   camUpz = 0.0f;
}

void Camera::mouseUpdate(const QVector2D& newMousePosition) {
    QVector2D mouseDelta = newMousePosition - oldMousePosition;
    QMatrix4x4 m;
    QVector3D viewDirection = {camViewx, camViewy, camViewz};

    m.rotate(mouseDelta.x(), camUpx, camUpy, camUpz);

    viewDirection = m * viewDirection;

    camViewx = viewDirection.x();
    camViewy = viewDirection.y();
    camViewz = viewDirection.z();

    oldMousePosition = newMousePosition;
}


void Camera::moveForward() {
    camPosx += speed * camViewx;
    camPosy += speed * camViewy;
    camPosz += speed * camViewz;
}

void Camera::moveBackward() {
    camPosx += -speed * camViewx;
    camPosy += -speed * camViewy;
    camPosz += -speed * camViewz;
}

void Camera::Left() {
    QVector3D View = {camViewx, camViewy, camViewz};
    QVector3D UP = {camUpx, camUpy, camUpz};
    QVector3D strafe = (QVector3D::crossProduct(View, UP));
    camPosx += -speed * strafe.x();
    camPosy += -speed * strafe.y();
    camPosz += -speed * strafe.z();

}
void Camera::Right() {
    QVector3D View = {camViewx, camViewy, camViewz};
    QVector3D UP = {camUpx, camUpy, camUpz};
    QVector3D strafe = (QVector3D::crossProduct(View, UP));
    camPosx += speed * strafe.x();
    camPosy += speed * strafe.y();
    camPosz += speed * strafe.z();

}

void Camera::Up() {
    camPosx += speed * camViewx;
    camPosy += speed * camViewy;
    camPosz += speed * camViewz;
}

void Camera::Down() {
    camPosx += -speed * camUpx;
    camPosy += -speed * camUpy;
    camPosz += -speed * camUpz;
}

void Camera::addPosY(double i) {
    camPosy += i;
}

void Camera::addPosX(double i) {
    camPosx += i;
}

void Camera::addPosZ(double i) {
    camPosz += i;
}

void Camera::addViewX(double i) {
    camViewx += i;
}

void Camera::addViewY(double i) {
    camViewy += i;
}

void Camera::addViewZ(double i) {
    camViewz += i;
}

void Camera::addUpX(double i) {
    camUpx += i;
}
void Camera::addUpY(double i) {
    camUpy += i;
}
void Camera::addUpZ(double i) {
    camUpz += i;
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

void Camera::changePos(double x, double y, double z) {
    camPosx = x;
    camPosy = y;
    camPosz = z;
}

void Camera::changeUp(double x, double y, double z) {
    camUpx = x;
    camUpy = y;
    camUpz = z;
}

void Camera::changeView(double x, double y, double z) {
    camViewx = x;
    camViewy = y;
    camViewz = z;
}


