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
    QVector3D getCameraLocation();
    QVector3D getCameraLookingDirection();
    Camera getCamera();
    QVector2D getMousePosition();
private:
    Camera *camera;

};

#endif // CAMERAVIEW_H
