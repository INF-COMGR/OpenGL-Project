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
    this->barrelView = new BarrelView(1, QVector3D(2, 0 , 4));
    this->barrelView2 = new BarrelView(2, QVector3D(8, 0, 10));

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
    glEnable(GL_DEPTH_TEST);
    //canvasf
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // ...Somewhere during initialization...
    // enable color tracking glEnable(GL_COLOR_MATERIAL);
    // set material properties which will be assigned by glColor glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // ...Somewhere in the main rendering loop of your program...
    // Draw a polygon with material properties set by glColor glColor3f(0.0f, 0.0f, 1.0f);
    // blue reflective properties glBegin(GL_TRIANGLES); glVertex3f(-1.0f, 0.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f); glEnd();
//    glEnable(GL_COLOR_MATERIAL);
//    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    // Create light components
        GLfloat ambientLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
        GLfloat diffuseLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
        //GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat position[] = { -0.2f, 1.0f, -0.3f, 0.0f };

        // Assign created components to GL_LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, position);


    timer->start(50);
    QRect rec = QApplication::desktop()->screenGeometry();
    QCursor::setPos(rec.width()/2, rec.height()/2);
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
    RoomView *room = new RoomView(0,0,0,  100,20,100,  255.0f,192.0f,203.0f);
    ShotgunView* shotgun = new ShotgunView();

    if (isWireframe) {
        GLfloat ambientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        //GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat position[] = { -0.2f, 1.0f, -0.3f, 0.0f };

        // Assign created components to GL_LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, position);

    } else {
        GLfloat ambientLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
        GLfloat diffuseLight[] = { 0.01f, 0.01f, 0.01f, 1.0f };
        //GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
        GLfloat position[] = { -0.2f, 1.0f, -0.3f, 0.0f };

        // Assign created components to GL_LIGHT0
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
        //glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
        glLightfv(GL_LIGHT0, GL_POSITION, position);

    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );

        shotgun->draw(isWireframe);
        this->cameraView->Draw();
        this->barrelView->draw(isWireframe);
        this->barrelView2->draw(isWireframe);
        room->draw(isWireframe);


    // restore current matrix
    glMatrixMode( GL_MODELVIEW );
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

