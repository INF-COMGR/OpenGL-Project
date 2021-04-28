#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QOpenGLWidget>
class QTimer;
class Space;
class CameraView;


class SpaceView : public QOpenGLWidget
{
public:
    SpaceView(QWidget *parent=0);

protected:
    void initializeGL ();
    void resizeGL ( int width, int height );
    void paintGL ();

    void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);

private:
    QTimer* timer;
    Space* space;
    CameraView* cameraView;

};

#endif // SPACEVIEW_H
