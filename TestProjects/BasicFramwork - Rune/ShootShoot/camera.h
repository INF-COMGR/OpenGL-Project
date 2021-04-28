#ifndef CAMERA_H
#define CAMERA_H
#include <QVector2D>
// include files for QT

class Camera
{

public:
    Camera();
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

    void moveForward();
    void moveBackward();
    void Left();
    void Right();
    void Up();
    void Down();

    void mouseUpdate(const QVector2D& newMousePosition);

private:
    float camPosx,camPosy,camPosz;
    float camUpx,camUpy,camUpz;
    float camViewx,camViewy,camViewz;
    float speed = 0.1f;
    QVector2D oldMousePosition;

};

#endif // CAMERA_H
