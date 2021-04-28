#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

// include files for QT
#include <QOpenGLWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include "camera.h"

class CameraView {
public:
    CameraView();
    void Draw();
    void keyPressEvent(QKeyEvent * e);
    void mouseMouveEvent(QMouseEvent* e);
/*protected:
    void initializeGL ();
    void resizeGL ( int width, int height );
    void paintGL ();

    void keyPressEvent(QKeyEvent * e);

private:
    double camPosx,camPosy,camPosz;
    double camUpx,camUpy,camUpz;
    double camViewx,camViewy,camViewz;
    QTimer* timer;*/
private:
    Camera *camera;

};

#endif // CAMERAVIEW_H
