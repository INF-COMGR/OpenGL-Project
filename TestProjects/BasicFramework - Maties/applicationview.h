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
class CameraView;
class BarrelView;

class ApplicationView : public QOpenGLWidget
{
    Q_OBJECT
public:
    ApplicationView(QWidget *parent=0);
protected:
    void initializeGL ();
    void resizeGL ( int width, int height );
    void paintGL ();

    void keyPressEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    CameraView *cameraView;
    BarrelView *barrelView;
    BarrelView *barrelView2;
    QTimer* timer;
    const int FPS_COUNT = 1000/120; //1 sec or 1000msec / 60FPS
};

#endif // APPLICATIONVIEW_H
