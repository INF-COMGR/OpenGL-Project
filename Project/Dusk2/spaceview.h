#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QTimer>
#include <QOpenGLWidget>
class ShotgunView;
class CameraView;
class BarrelView;
class RoomView;

class SpaceView: public QOpenGLWidget {
public:
    SpaceView(QWidget *parent=0, bool isWireframe = false);

protected:
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

private:
    QTimer* timer;
    CameraView* cameraView;
    BarrelView* barrelView;
    BarrelView* barrelView2;
    ShotgunView* shotgunView;
    RoomView* roomView;
    void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);
    const int FPS_COUNT = 1000/120; //1 sec or 1000msec / 120FPS
    bool isWireframe = false;

};
#endif // SPACEVIEW_H
