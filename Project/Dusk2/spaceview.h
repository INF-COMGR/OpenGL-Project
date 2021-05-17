#ifndef SPACEVIEW_H
#define SPACEVIEW_H
#include <QTimer>
#include <QOpenGLWidget>
#include <QLabel>
#include <QSoundEffect>
#include "picking.h"

class ShotgunView;
class CameraView;
class BarrelView;
class RoomView;
class BulletView;
class HitBox;

class SpaceView: public QOpenGLWidget {
public:
    SpaceView(QWidget *parent=0, bool isWireframe = false);

protected:
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();

private:
    //void addHitboxes(QVector<HitBox*>* needsAdding);
    QTimer* timer;
    CameraView* cameraView;
    QVector<BarrelView*> barrels;
    ShotgunView* shotgunView;
    RoomView* roomView;
    BulletView* bulletView;
    void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    const int FPS_COUNT = 1000/120; //1 sec or 1000msec / 120FPS
    bool isWireframe = false;

    bool gotAllBarrels();
    QLabel* scoreLabel;
    QLabel* explanationLabel;
    QLabel* pickingLabel;
    const int BEGIN_SCORE = 10000;
    int penalty = 0;
    void updateScore();

    QSoundEffect* shotGunSound;
    QSoundEffect* winningSound;
    bool winningSoundPlayed = false;

    void restart();
};
#endif // SPACEVIEW_H
