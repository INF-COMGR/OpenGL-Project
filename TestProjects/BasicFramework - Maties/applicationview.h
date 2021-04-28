#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include <QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QVector3D>
#include <QMatrix4x4>
#include "util.h"
#include <QMouseEvent>
#include <QCursor>
#include <QApplication>
#include <QDesktopWidget>

class ApplicationView : public QOpenGLWidget
{
    Q_OBJECT
public:
    ApplicationView(QWidget *parent=0);
    void changeCam(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ);
    void mouseUpdate(const QVector2D& movedMouse2DVec);
protected:
    void initializeGL ();
    void resizeGL ( int width, int height );
    void paintGL ();

    void keyPressEvent(QKeyEvent * e);
private:

    int secondsPassed;
    QTimer* timer;


    //NAVIGATION
    /*
    camPosx = 10.0,  camPosy = 0.0, camPosz = 0.0;
    camViewx = 0.0, camViewy = 0.0, camViewz = 0.0;
    camUpx = 0.0,   camUpy = 1.0,   camUpz = 0.0;
    */
    QVector3D position = *new QVector3D(10, 0, 0);
    QVector3D view = *new QVector3D(0, 0, 0);
    QVector3D UP = *new QVector3D(0, 1, 0);
    QVector2D currentMouse2DVec = *new QVector2D(0, 0);
    void mouseMoveEvent(QMouseEvent*);
    QVector3D getStrafeVector();

    const float MOVEMENT_SPEED = 0.01f;
    void goForward();
    void goBackward();
    void strafeLeft();
    void strafeRight();
    void goUp();
    void goDown();

    //MATERIAL
    float globePos = 5.0f;
    void moveGlobeDownLine();
    void moveGlobeUpLine();

    void movePlayer( QKeyEvent * e );
};

#endif // APPLICATIONVIEW_H
