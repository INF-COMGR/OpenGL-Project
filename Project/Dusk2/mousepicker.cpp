#include "mousepicker.h"
#include "math.h"


MousePicker::MousePicker(Camera camera)
{
    this->camera = camera;
}

void MousePicker::update() {
    this->latestView = this->camera.getViewVector();
    this->latestView = this->latestView.normalized();
}

QVector3D MousePicker::getLatestView() {
    return this->latestView;
}

void MousePicker::normalize() {
    //float length = sqrt(latestView[0] * latestView[0] + latestView[1] * latestView[1] + latestView[2] * latestView[2]);



}
