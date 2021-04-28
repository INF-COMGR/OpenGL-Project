#include "camera.h"
#include <QVector2D>
#include <QVector3D>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>

Camera::Camera() {
    position = new QVector3D(10, 0, 0);
    view = new QVector3D(0, 0, 0);
    UP = new QVector3D(0, 1, 0);
    currentMouse2DVec = new QVector2D(0, 0);
}

void Camera::changeCam(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ)
{
    position->setX(posX);
    position->setY(posY);
    position->setZ(posZ);

    view->setX(lookAtX);
    view->setY(lookAtY);
    view->setZ(lookAtZ);

    *view += *position;

    UP->setX(upX);
    UP->setY(upY);
    UP->setZ(upZ);
}

QVector3D Camera::getStrafeVector() {
    return QVector3D::crossProduct(*view, *UP);         //get StrafeVector
}

void Camera::keyUpdate(QKeyEvent *e) {
    if (isFreeCam)
        freeCamEvent(e);
    else
        walkCamEvent(e);
}

void Camera::mouseUpdate(QVector2D *movedMouse2DVec) {
    const float rotationSpeed = -0.1f;
    QVector2D delta = *movedMouse2DVec - *currentMouse2DVec;

    //horizontal rotation
    QMatrix4x4* horizontalRotationM = new QMatrix4x4();
    horizontalRotationM->setToIdentity();
    horizontalRotationM->rotate(delta.x()*rotationSpeed, *UP);            //rotate around UP Vector
    *view = *horizontalRotationM * *view;

    //vertical rotation
    QMatrix4x4 *verticalRotationM = new QMatrix4x4();
    verticalRotationM->setToIdentity();
    QVector3D StrafeVector = getStrafeVector();
    verticalRotationM->rotate(delta.y()*rotationSpeed, StrafeVector);    //rotate around Strafe Vector
    *view = *verticalRotationM * *view;

    //Resetting mouse to middlepoint
    QRect rec = QApplication::desktop()->screenGeometry();
    currentMouse2DVec = new QVector2D(rec.width()/2, rec.height()/2);
    QCursor::setPos(rec.width()/2, rec.height()/2);
}

void Camera::freeCamEvent(QKeyEvent* e) {
    switch(e->key()) {
    case Qt::Key::Key_Z:
        goForward();
        break;
    case Qt::Key::Key_S:
        goBackward();
        break;
    case Qt::Key::Key_Q:
        strafeLeft();
        break;
    case Qt::Key::Key_D:
        strafeRight();
        break;
    case Qt::Key::Key_A:
        goDown();
        break;
    case Qt::Key::Key_E:
        goUp();
        break;
    case Qt::Key::Key_O:
        moveGlobeDownLine();
        break;
    case Qt::Key::Key_L:
        moveGlobeUpLine();
        break;
    }
}

void Camera::walkCamEvent(QKeyEvent *e) {
    switch(e->key()) {
    case Qt::Key::Key_Z:
        walkForward();
        break;
    case Qt::Key::Key_S:
        walkBackward();
        break;
    case Qt::Key::Key_Q:
        walkLeft();
        break;
    case Qt::Key::Key_D:
        walkRight();
        break;
    }
}

void Camera::moveGlobeUpLine() {
    globePos++;
}

void Camera::moveGlobeDownLine() {
    globePos--;
}

//Flying
void Camera::toggleFreeCam() {
    isFreeCam = isFreeCam ? false : true;
}

void Camera::goForward() {
    *position += MOVEMENT_SPEED * *view;
}
void Camera::goBackward() {
    *position += -MOVEMENT_SPEED * *view;
}
void Camera::strafeLeft() {
    QVector3D StrafeVector = getStrafeVector();
    *position += -MOVEMENT_SPEED * StrafeVector;
}
void Camera::strafeRight() {
    QVector3D StrafeVector = getStrafeVector();
    *position += MOVEMENT_SPEED * StrafeVector;
}
void Camera::goUp() {
    *position += MOVEMENT_SPEED*5 * *UP;
}
void Camera::goDown() {
    *position += -MOVEMENT_SPEED*5 * *UP;
}

//Walking
void Camera::walkForward() {
    *position += MOVEMENT_SPEED * *view;
    position->setY(CAMERA_HEIGHT);

}
void Camera::walkBackward() {
    *position += -MOVEMENT_SPEED * *view;
    position->setY(CAMERA_HEIGHT);
}
void Camera::walkLeft() {
    QVector3D StrafeVector = getStrafeVector();
    *position += -MOVEMENT_SPEED * StrafeVector;
    position->setY(CAMERA_HEIGHT);
}
void Camera::walkRight() {
    QVector3D StrafeVector = getStrafeVector();
    *position += MOVEMENT_SPEED * StrafeVector;
    position->setY(CAMERA_HEIGHT);
}

void Camera::addPosX(double i) {
    position->setX(position->x()+i);
}

void Camera::addPosY(double i) {
    position->setY(position->y()+i);
}

void Camera::addPosZ(double i) {
    position->setZ(position->z()+i);
}

void Camera::addViewX(double i) {
    view->setX(view->x()+i);
}

void Camera::addViewY(double i) {
    view->setY(view->y()+i);
}

void Camera::addViewZ(double i) {
    view->setZ(view->z()+i);
}

void Camera::addUpX(double i) {
    UP->setX(UP->x()+i);
}
void Camera::addUpY(double i) {
    UP->setY(UP->y()+i);
}
void Camera::addUpZ(double i) {
    UP->setZ(UP->z()+i);
}

double Camera::getPosX() {
    return position->x();
}
double Camera::getPosY() {
    return position->y();
}
double Camera::getPosZ() {
    return position->z();
}
double Camera::getViewX() {
    return view->x();
}
double Camera::getViewY() {
    return view->y();
}
double Camera::getViewZ() {
    return view->z();
}
double Camera::getUpX() {
    return UP->x();
}
double Camera::getUpY() {
    return UP->y();
}
double Camera::getUpZ() {
    return UP->z();
}

void Camera::changePos(double x, double y, double z) {
    position->setX(x);
    position->setY(y);
    position->setZ(z);
}
void Camera::changeView(double x, double y, double z) {
    view->setX(x);
    view->setY(y);
    view->setZ(z);
}
void Camera::changeUp(double x, double y, double z) {
    UP->setX(x);
    UP->setY(y);
    UP->setZ(z);
}
