#ifndef CAMERA_H
#define CAMERA_H
#include <QVector3D>
#include <QVector2D>
class QMouseEvent;
class QKeyEvent;

class Camera
{
public:
    Camera();
    void changeCam(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ);
    void keyUpdate(QKeyEvent *e);
    void mouseUpdate(QVector2D *movedMouse2DVec);
    void toggleFreeCam();

    void changePos(double x, double y, double z);
    void changeUp(double x, double y, double z);
    void changeView(double x, double y, double z);
    void addPosY(double i);
    void addPosX(double i);
    void addPosZ(double i);
    void addViewY(double i);
    void addViewX(double i);
    void addViewZ(double i);
    void addUpY(double i);
    void addUpX(double i);
    void addUpZ(double i);
    double getPosX();
    double getPosY();
    double getPosZ();
    double getViewX();
    double getViewY();
    double getViewZ();
    double getUpX();
    double getUpY();
    double getUpZ();


private:
    QVector3D *position;
    QVector3D *view;
    QVector3D *UP;
    QVector2D *currentMouse2DVec;
    void mouseMoveEvent(QMouseEvent*);
    QVector3D getStrafeVector();
    bool isFreeCam = true;
    void freeCamEvent(QKeyEvent* e);
    void walkCamEvent(QKeyEvent* e);


    const float MOVEMENT_SPEED = 0.01f;
    void goForward();
    void goBackward();
    void strafeLeft();
    void strafeRight();
    void goUp();
    void goDown();

    const float CAMERA_HEIGHT = 1.0f;
    void walkForward();
    void walkBackward();
    void walkLeft();
    void walkRight();

    //MATERIAL
    float globePos = 5.0f;
    void moveGlobeDownLine();
    void moveGlobeUpLine();

    //void movePlayer( QKeyEvent * e );
};

#endif // CAMERA_H
