#include "applicationview.h"

ApplicationView::ApplicationView(QWidget *parent) : QOpenGLWidget(parent)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setFocusPolicy(Qt::StrongFocus);

    cameraView = new CameraView;
    cameraView->changeCam(2, 2, 25, 0, 0, -1, 0, 1, 0);
    cameraView->toggleFreeCam();
}

void ApplicationView::initializeGL()
{
    // Initialize QGLWidget (parent)
    QOpenGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    // Black canvas
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable(GL_DEPTH_TEST);

    GLfloat light0_position [] = {20.0f, 20.0f, 20.0f, 1.0f};
    GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glEnable(GL_DEPTH_TEST);

    timer->start(FPS_COUNT);
}

void ApplicationView::resizeGL(int width, int height)
{
    if ((width<=0) || (height<=0))
        return;

    //set viewport
    setMouseTracking(true);
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //set persepective
    //change the next line order to have a different perspective
    GLdouble aspect_ratio=(GLdouble)width/(GLdouble)height;
    gluPerspective(40.0, aspect_ratio, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ApplicationView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glEnable( GL_LIGHTING );

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );

    cameraView->Draw();


    Util::drawSolidSphere(3.0, 25, 25);
    Util::drawSolidCuboid({0, 3, 0}, {3, 0, 3});

    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(5, 5, 5);
        glColor3f(0, 1, 0);
        glVertex3f(6, 5, 6);
        glColor3f(0, 0, 1);
        glVertex3f(5, 6, 5);
    glEnd();

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    //MATERIALS
    /*
    glPushMatrix();
        GLfloat ambient [] = {0.13f, 0.22f, 0.15f, 0.95f};
        glMaterialfv ( GL_FRONT, GL_AMBIENT, ambient );
        Util::drawSolidSphere(3.0, 25, 25);
    glPopMatrix();

    glTranslated(7, 0, 0);
    */

    /*
    glDisable(GL_COLOR_MATERIAL);
    glPushMatrix();
        glTranslated(globePos, 0, 0);
        //GLfloat shin [] = {12.8f};
        GLfloat diff [] = {0.0f, 0.0f, 1.0f, 0.95f};
        glMaterialfv ( GL_FRONT, GL_DIFFUSE, diff );
        //GLfloat specular [] = {0.1f, 0.1f, 0.1f, 0.95f};
        //glMaterialfv ( GL_FRONT, GL_AMBIENT, specular );
        Util::drawSolidSphere(3.0, 25, 25);
    glPopMatrix();
    glEnable(GL_COLOR_MATERIAL);

    glDisable(GL_COLOR_MATERIAL);
    glPushMatrix();
        GLfloat diff2 [] = {1.0f, 0.0f, 0.0f, 0.95f};
        glMaterialfv ( GL_FRONT, GL_DIFFUSE, diff2 );
        //GLfloat specular2 [] = {0.1f, 0.1f, 0.1f, 0.95f};
        //glMaterialfv ( GL_FRONT, GL_SPECULAR, specular );
        Util::drawSolidSphere(3.0, 25, 25);
    glPopMatrix();
    glEnable(GL_COLOR_MATERIAL);
    */
    //LIGHTING
    /*
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {position.x(), position.y(), position.z()};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
    GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
    GLfloat light_direction[] = {view.x(), view.y(), view.z()};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
    */
}

void ApplicationView::mouseMoveEvent(QMouseEvent *e) {
    cameraView->mouseMoveEvent(e);
}

void ApplicationView::keyPressEvent( QKeyEvent * e ) {
    cameraView->keyPressedEvent(e);
}
