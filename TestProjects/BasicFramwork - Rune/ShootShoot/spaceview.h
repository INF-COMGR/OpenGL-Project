#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QOpenGLWidget>
#include <QTimer>
#include "space.h"
#include "cameraview.h"

class SpaceView: public QOpenGLWidget
{
public:
    SpaceView(QWidget *parent=0);
private:
    QTimer* timer;
    //space* space;
    CameraView* cameraView;
    void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);

protected:
    void initializeGL ();
    void resizeGL ( int width, int height );
    void paintGL ();
};

#endif // SPACEVIEW_H
