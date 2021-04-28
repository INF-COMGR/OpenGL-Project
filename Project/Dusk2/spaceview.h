#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QTimer>
#include <QOpenGLWidget>
class CameraView;

class SpaceView: public QOpenGLWidget {
public:
    SpaceView(QWidget *parent=0);
private:
    QTimer* timer;
    CameraView* cameraView;
    void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);

protected:
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();
};
#endif // SPACEVIEW_H
