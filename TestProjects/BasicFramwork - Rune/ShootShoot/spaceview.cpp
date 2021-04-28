#include "spaceview.h"
#include "roomview.h"
#include "util.h"

SpaceView::SpaceView(QWidget *parent) : QOpenGLWidget(parent) {
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);

}

void SpaceView::initializeGL () {
    //setMouseTracking(true);

    QOpenGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    // Black canvasf
    glClearColor(137.0f/255.0f,207.0f/255.0f,240.0f/255.0f,1.0f);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_DEPTH_TEST);

    GLfloat light0_position [] = {-3.0f, -5.0f, -25.0f, 0.0f};
    GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );

    timer->start(50);

    this->cameraView = new CameraView();



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
    RoomView* room = new RoomView(5,5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    this->cameraView->Draw();
//            gluLookAt( -3.0f, -5.0f, -25.0f,
//                       0.0f, 0.0f, -1.0f,
//                       0.0f, 1.0f, 0.0f);

//                        //camPosx ,camPosy ,camPosz,
//                      //camViewx,camViewy,camViewz,
//                      //camUpx, camUpy, camUpz );

//            //Draw Axes
//            glDisable( GL_LIGHTING );
//            glBegin(GL_LINES);
//                glColor3f(1.0, 0.0, 0.0);
//                glVertex3f(0.0, 0.0, 0.0);
//                glVertex3f(10.0, 0.0, 0.0);
//                glColor3f(0.0, 1.0, 0.0);
//                glVertex3f(0.0, 0.0, 0.0);
//                glVertex3f(0.0, 10.0, 0.0);
//                glColor3f(0.0, 0.0, 1.0);
//                glVertex3f(0.0, 0.0, 0.0);
//                glVertex3f(0.0, 0.0, 10.0);
//            glEnd();
//            glEnable( GL_LIGHTING );
        glRotated ( 5.0, 1.0, 0.0, 0.0 );
        glPushMatrix();
            room->Draw();
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
