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
class Cube;
class button;
class AnimationView;

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
    Cube* littleWall1;
    Cube* littleWall2;
    button* giveUpButton;
    button* restartButton;
    AnimationView* animationView;
    AnimationView* animationView2;
    AnimationView* animationView3;
    void keyPressEvent(QKeyEvent * e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void handlePicking(QKeyEvent* e);
    bool gotAllBarrels();

    const int FPS_COUNT = 1000/120; //1 sec or 1000msec / 120FPS
    bool isWireframe = false;
    bool gaveUp = false;

    QLabel* scoreLabel;
    QLabel* explanationLabel;
    QLabel* pickingLabel;
    QLabel* pickingBlockRestart;
    QLabel* pickingBlockGiveUp;

    const int BEGIN_SCORE = 2000;
    int penalty = 0;
    void updateScore();

    QSoundEffect* shotGunSound;
    QSoundEffect* winningSound;
    QSoundEffect* losingSound;

    bool winningSoundPlayed = false;
    bool losingSoundPlayed = false;


    void restart();
    void lose();
    void initBarrels();
};
#endif // SPACEVIEW_H
