#include "spaceview.h"
#include "util.h"
#include "cameraview.h"
#include "barrelview.h"
#include <QKeyEvent>
#include "roomview.h"
#include "shotgunview.h"
#include "bulletview.h"
#include "hitbox.h"

#include "QKeyEvent"
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>


SpaceView::SpaceView(QWidget *parent, bool isWireframe) : QOpenGLWidget(parent) {
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);

    this->cameraView = new CameraView;
    this->isWireframe = isWireframe;

    scoreLabel = new QLabel("\nTEST", this);
    explanationLabel = new QLabel("\nUse your mouse to move and click to shoot.\nShoot all the barrels to win!\n W - toggle wireframe | F - toggle noclip", this);
    this->bulletView = nullptr;

    shotGunSound = new QSoundEffect(this);
    shotGunSound->setSource(QUrl::fromLocalFile(":/:/shotgunsound.wav"));
    shotGunSound->setLoopCount(1);
    shotGunSound->setVolume(0.05f);

    winningSound = new QSoundEffect(this);
    winningSound->setSource(QUrl::fromLocalFile(":/:/winningsound.wav"));
    winningSound->setLoopCount(1);
    winningSound->setVolume(0.2f);
}

/**
 * Standard initializer (might still need changes)
 *
 * @brief SpaceView::initializeGL
 */
void SpaceView::initializeGL () {
    setMouseTracking(true);
    QOpenGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    //canvasf
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_DEPTH_TEST);

    GLfloat light0_position [] = {0.2f, 1.0f, 0.3f, 0.0f};
    GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_ambient []={ 1.0, 1.0, 1.0, 1.0 };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);

    timer->start(FPS_COUNT);
    QRect rec = QApplication::desktop()->screenGeometry();
    QCursor::setPos(rec.width()/2, rec.height()/2);

    //Init models with textures & logic
    this->roomView = new RoomView(0,0,0,  50,20,50,  255.0f,192.0f,203.0f);
    this->shotgunView = new ShotgunView();
    this->barrels.append(new BarrelView(1, QVector3D(2, 7, 2)));        //small barrel (size 1) on top of big barrel begin view
    this->barrels.append(new BarrelView(2, QVector3D(2, 4, 2)));        //big barrel (size 2) under small barrel begin view
    this->barrels.append(new BarrelView(5, QVector3D(10, 10, 10)));     //giant barrel (size 5) to the side
    this->barrels.append(new BarrelView(1, QVector3D(10, 30, 10)));     //small barrel 1 (size 1) on top of giant barrel
    this->barrels.append(new BarrelView(1, QVector3D(10, 40, 10)));     //small barrel 2 (size 1) on top of giant barrel
    this->barrels.append(new BarrelView(1, QVector3D(10, 50, 10)));     //small barrel 3 (size 1) on top of giant barrel

    this->barrels.append(new BarrelView(2, QVector3D(30, 40, 20)));
    this->barrels.append(new BarrelView(2, QVector3D(20, 35, 30)));

    this->barrels.append(new BarrelView(1, QVector3D(35, 10, 25)));
    this->barrels.append(new BarrelView(1, QVector3D(25, 15, 35)));

    for(int i = 0; i < barrels.length(); ++i) {
        barrels[i]->setFalling();
        for(int j = 0; j < barrels.length(); ++j) {
            if (i != j)
                barrels[i]->addHitBox(barrels[j]->getHitBox());
        }
    }
}

/**
 * Standard resizeGL function (might still need changes)
 *
 * @brief SpaceView::resizeGL
 * @param width
 * @param height
 */
void SpaceView::resizeGL ( int width, int height ) {
    if ((width<=0) || (height<=0))
        return;

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble aspect_ratio=(GLdouble)width/(GLdouble)height;

    gluPerspective(40.0, aspect_ratio, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SpaceView::updateScore()
{
    if (!gotAllBarrels()) {
        penalty += 1;
        if (penalty % 10 == 0) {
            scoreLabel->setText("current score: "+QString::number(BEGIN_SCORE-penalty));
            scoreLabel->adjustSize();
        }
    } else {
        scoreLabel->setText("FINAL SCORE: "+QString::number(BEGIN_SCORE-penalty));
        scoreLabel->adjustSize();
    }
}

void SpaceView::paintGL () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    updateScore();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
        this->shotgunView->draw(isWireframe);
        this->cameraView->Draw();
        for (int i = 0; i < barrels.length(); ++i)
            barrels[i]->draw(isWireframe);

        this->roomView->draw(isWireframe);
        if (bulletView != nullptr)
            bulletView->draw(isWireframe);
    glPopMatrix( );
}

void SpaceView::keyPressEvent(QKeyEvent * e) {
    if (e->key() == Qt::Key::Key_W)
        this->isWireframe = this->isWireframe ? false : true;
    cameraView->keyPressEvent(e);

}

void SpaceView::mouseMoveEvent(QMouseEvent *e) {
    cameraView->mouseMouveEvent(e);
}

void SpaceView::mousePressEvent(QMouseEvent *e) {
    shotGunSound->play();
    this->bulletView = new BulletView(cameraView->getCameraLocation(), cameraView->getCameraLookingDirection());
    QVector<HitBox*> roomHitboxes = roomView->getHitBoxes();
    for (int i = 0; i < roomHitboxes.length(); ++i) {
        this->bulletView->addHitBox(roomHitboxes[i]);
    }
    for (int i = 0; i < barrels.length(); ++i) {
        this->bulletView->addHitBox(barrels[i]->getHitBox());
    }

}

bool SpaceView::gotAllBarrels() {
    for (int i = 0; i < barrels.length(); ++i) {
        if (!barrels[i]->getHitBox()->getHitByBullet())
            return false;
    }
    if (!winningSoundPlayed)
        winningSound->play();
    winningSoundPlayed = true;
    return true;
}


