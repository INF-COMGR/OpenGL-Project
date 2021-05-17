#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

// include files for QT
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include "camera.h"
#include "picking.h"

class CameraView {
public:
    CameraView();
    void Draw();
    void keyPressEvent(QKeyEvent * e);
    void mouseMouveEvent(QMouseEvent* e);
    QVector3D getCameraLocation();
    QVector3D getCameraLookingDirection();
    int pick();
private:
    Camera *camera;
    picking* picking = new class picking();

};

#endif // CAMERAVIEW_H
