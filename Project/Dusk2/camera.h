#ifndef CAMERA_H
#define CAMERA_H
#include <QVector2D>
// include files for QT

class Camera
{

public:
    Camera();
    double getPosX();
    double getPosY();
    double getPosZ();
    double getViewX();
    double getViewY();
    double getViewZ();
    double getUpX();
    double getUpY();
    double getUpZ();

    void walkForward();
    void walkBackward();
    void walkLeft();
    void walkRight();

    void flyForward();
    void flyBackward();
    void flyLeft();
    void flyRight();

    bool isFlying();
    void toggleFlying();

    void mouseUpdate(const QVector2D& newMousePosition);

private:
    QVector3D getStrafe();
    float camPosx,camPosy,camPosz;
    float camUpx,camUpy,camUpz;
    float camViewx,camViewy,camViewz;
    float speed = 0.3f;
    float cameraHeight = 2.0f;
    QVector2D oldMousePosition;
    bool flying;

};

#endif // CAMERA_H
