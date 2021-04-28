#include "spaceview.h"
#include <QTimer>
#include "space.h"
#include "cameraview.h"
#include "globeview.h"
#include "util.h"
#include "lightview.h"

SpaceView::SpaceView(QWidget *parent) : QOpenGLWidget(parent)
{
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);
}


void SpaceView::initializeGL () {
    setMouseTracking(true);
    // Initialize QGLWidget (parent)
    QOpenGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    // Black canvasf
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_DEPTH_TEST);

    GLfloat light0_position [] = {0.1f, 0.1f, 0.1f, 0.1f};
    GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );

    timer->start(50);

    cameraView = new CameraView();

}

void SpaceView::resizeGL ( int width, int height ) {
    if ((width<=0) || (height<=0))
        return;

    //set viewport
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION); //initialise projection matrix (selecteer op welke matrix je gaat werken)
    glLoadIdentity(); //overschrijf matrix met identiteit

    //set persepective
    //change the next line order to have a different perspective
    GLdouble aspect_ratio=(GLdouble)width/(GLdouble)height;

    /*
     * @brief gluPerspective
     * eerste argument: fovy (???)
     * tweede argument: aspect_ratio: coordinaten juist mappen voor schermverhouding
     * derde argument: Z_near: z-as vanaf waar er wordt gestart met tekenen
     * vierde argument: Z_far: vanaf waar er wordt gestopt met tekenen
     */
    gluPerspective(40.0, aspect_ratio, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * ALLE model: moeten een update functie hebben
 * ALLE view: een draw functie hebben
 *
*/


void SpaceView::paintGL () {
    GlobeView* globeView = new GlobeView(5, 0.5f, 0.2f, 0.1f );
    GlobeView* globeView2 = new GlobeView(2, 0.2f, 0.0f, 0.1f );
    GlobeView* globeView3 = new GlobeView(1, 0.0f, 0.2f, 0.4f );

    LightView* lightView = new LightView(3.0, 5.0, 25.0, 0.0, 2.0, 2.0, 8.0, 1.0);
    //LightView* lightView;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
        cameraView->Draw();
        glRotated ( 5.0, 1.0, 0.0, 0.0 );
        glPushMatrix();
            globeView->Draw(GL_SMOOTH, GL_FRONT,GL_DIFFUSE);
        glPopMatrix();
        glPushMatrix();
            glTranslated(0.5, 10, 1);
            globeView2->Draw(GL_SMOOTH, GL_FRONT,GL_DIFFUSE);
        glPopMatrix();

        glPushMatrix();
        glTranslated(15, 1, 1);
            globeView3->Draw(GL_SMOOTH, GL_FRONT,GL_DIFFUSE);
        glPopMatrix();

        glPushMatrix();
        //unsigned long lighting, unsigned long light, unsigned long position, unsigned long diffusion
            lightView->Draw(GL_LIGHTING, GL_LIGHT2, GL_POSITION,  GL_DIFFUSE);
        glPopMatrix();


    // restore current matrix
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );

}

void SpaceView::keyPressEvent(QKeyEvent * e) {
    cameraView->keyPressEvent(e);
}

void SpaceView::mouseMoveEvent(QMouseEvent *e) {
    cameraView->mouseMouveEvent(e);
}
