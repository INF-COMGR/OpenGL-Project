#include "applicationview.h"

ApplicationView::ApplicationView(QWidget *parent) : QOpenGLWidget(parent)
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    setFocusPolicy(Qt::StrongFocus);
}

void ApplicationView::changeCam(float posX, float posY, float posZ, float lookAtX, float lookAtY, float lookAtZ, float upX, float upY, float upZ)
{
    position.setX(posX);
    position.setY(posY);
    position.setZ(posZ);

    view.setX(lookAtX);
    view.setY(lookAtY);
    view.setZ(lookAtZ);

    view += position;

    UP.setX(upX);
    UP.setY(upY);
    UP.setZ(upZ);
}

void ApplicationView::initializeGL()
{
    secondsPassed = 0;

    // Initialize QGLWidget (parent)
    QOpenGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    // Black canvas
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable(GL_DEPTH_TEST);

    timer->start(50);
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
    secondsPassed++;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
    glEnable( GL_LIGHTING );
    gluLookAt(position.x(),position.y(), position.z(),
              view.x(), view.y(), view.z(),
              UP.x(), UP.y(), UP.z());

    /*
    glPushMatrix();
        GLfloat ambient [] = {0.13f, 0.22f, 0.15f, 0.95f};
        glMaterialfv ( GL_FRONT, GL_AMBIENT, ambient );
        Util::drawSolidSphere(3.0, 25, 25);
    glPopMatrix();

    glTranslated(7, 0, 0);
    */

    //Draw Axes
    glDisable( GL_LIGHTING );
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glEnable( GL_LIGHTING );
    glEnable(GL_COLOR_MATERIAL);

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

    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {position.x(), position.y(), position.z()};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0f);
    GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color);
    GLfloat light_direction[] = {view.x(), view.y(), view.z()};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}

void ApplicationView::mouseMoveEvent(QMouseEvent *event) {
    mouseUpdate(QVector2D(event->x(), event->y()));
}

QVector3D ApplicationView::getStrafeVector() {
    return QVector3D::crossProduct(view, UP);         //get StrafeVector
}

void ApplicationView::mouseUpdate(const QVector2D &movedMouse2DVec) {
    const float rotationSpeed = -0.1f;
    QVector2D delta = movedMouse2DVec - currentMouse2DVec;

    //horizontal rotation
    QMatrix4x4 horizontalRotationM = *new QMatrix4x4();
    horizontalRotationM.setToIdentity();
    horizontalRotationM.rotate(delta.x()*rotationSpeed, UP);            //rotate around UP Vector
    view = horizontalRotationM * view;

    //vertical rotation
    QMatrix4x4 verticalRotationM = *new QMatrix4x4();
    verticalRotationM.setToIdentity();
    QVector3D StrafeVector = getStrafeVector();
    verticalRotationM.rotate(delta.y()*rotationSpeed, StrafeVector);    //rotate around Strafe Vector
    view = verticalRotationM * view;

    //Resetting mouse to middlepoint
    QRect rec = QApplication::desktop()->screenGeometry();
    currentMouse2DVec = QVector2D(rec.width()/2, rec.height()/2);
    QCursor::setPos(rec.width()/2, rec.height()/2);
}

void ApplicationView::keyPressEvent( QKeyEvent * e ) {
    switch(e->key()) {
    case Qt::Key::Key_Z:
        goForward();
        break;
    case Qt::Key::Key_S:
        goBackward();
        break;
    case Qt::Key::Key_Q:
        strafeLeft();
        break;
    case Qt::Key::Key_D:
        strafeRight();
        break;
    case Qt::Key::Key_A:
        goDown();
        break;
    case Qt::Key::Key_E:
        goUp();
        break;
    case Qt::Key::Key_O:
        moveGlobeDownLine();
        break;
    case Qt::Key::Key_L:
        moveGlobeUpLine();
        break;
    }
}

void ApplicationView::moveGlobeUpLine() {
    globePos++;
}

void ApplicationView::moveGlobeDownLine() {
    globePos--;
}

void ApplicationView::goForward() {
    position += MOVEMENT_SPEED * view;
}
void ApplicationView::goBackward() {
    position += -MOVEMENT_SPEED * view;
}
void ApplicationView::strafeLeft() {
    QVector3D StrafeVector = getStrafeVector();
    position += -MOVEMENT_SPEED * StrafeVector;
}
void ApplicationView::strafeRight() {
    QVector3D StrafeVector = getStrafeVector();
    position += MOVEMENT_SPEED * StrafeVector;
}
void ApplicationView::goUp() {
    position += MOVEMENT_SPEED*5 * UP;
}
void ApplicationView::goDown() {
    position += -MOVEMENT_SPEED*5 * UP;
}
