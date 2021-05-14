#include "spaceview.h"
#include "util.h"
#include "cameraview.h"
#include "barrelview.h"
#include <QKeyEvent>
#include "roomview.h"
#include "shotgunview.h"

#include "QKeyEvent"
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>


SpaceView::SpaceView(QWidget *parent, bool isWireframe) : QOpenGLWidget(parent) {


    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);

    this->cameraView = new CameraView;
    this->barrelView = new BarrelView(1, QVector3D(2, 0 , 0));
    this->barrelView2 = new BarrelView(2, QVector3D(-2, 0, 0));

    this->isWireframe = isWireframe;

    this->cameraView = new CameraView();
    //this->cameraView->changeCam(2, 2, 25, 0, 0, -1, 0, 1, 0);
    //this->cameraView->toggleFreeCam();
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

    GLfloat light0_position [] = {0.1f, 0.1f, 0.1f, 0.1f};
    GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );

    timer->start(10);
    QRect rec = QApplication::desktop()->screenGeometry();
    QCursor::setPos(rec.width()/2, rec.height()/2);

    this->roomView = new RoomView(0,0,0,  50,20,50,  255.0f,192.0f,203.0f);
    this->shotgunView = new ShotgunView();

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

void SpaceView::paintGL () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
        this->shotgunView->draw(isWireframe);
        this->cameraView->Draw();
        this->barrelView->draw(isWireframe);
        this->roomView->draw(isWireframe);
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

