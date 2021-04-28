#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H
class QKeyEvent;
class QMouseEvent;
class Camera;

class CameraView
{
public:
    CameraView();
    void Draw();
    void keyPressedEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void toggleAxis();
    void changeCam(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ);
    void toggleFreeCam();
private:
    Camera *camera;
    bool axisEnabled = true;
};

#endif // CAMERAVIEW_H
