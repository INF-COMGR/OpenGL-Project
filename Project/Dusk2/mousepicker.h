#ifndef MOUSEPICKER_H
#define MOUSEPICKER_H

#include <QVector3D>
#include "camera.h"

class MousePicker
{
public:
    MousePicker(Camera camera);
    void update();
    QVector3D getLatestView();
    void normalize();

private:
    Camera camera;
    QVector3D latestView;
};

#endif // MOUSEPICKER_H
