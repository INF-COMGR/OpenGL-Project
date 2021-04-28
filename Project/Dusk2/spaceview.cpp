#include "spaceview.h"
#include "util.h"
#include "cameraview.h"

SpaceView::SpaceView(QWidget *parent) : QOpenGLWidget(parent) {
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);

    this->cameraView = new CameraView;
    this->cameraView->changeCam(2, 2, 25, 0, 0, -1, 0, 1, 0);
    this->cameraView->toggleFreeCam();
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

    timer->start(50);

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
        this->cameraView->Draw();
    // restore current matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );
}

void SpaceView::keyPressEvent(QKeyEvent * e) {
    cameraView->keyPressedEvent(e);
}

void SpaceView::mouseMoveEvent(QMouseEvent *e) {
    cameraView->mouseMoveEvent(e);
}

