#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

// include files for QT
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "camera.h"

class CameraView {
public:
    CameraView();
    void Draw();
    void keyPressEvent(QKeyEvent * e);
    void mouseMouveEvent(QMouseEvent* e);
private:
    Camera *camera;

};

#endif // CAMERAVIEW_H
