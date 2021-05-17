#include "spaceview.h"

#include "cameraview.h"
#include "barrelview.h"
#include <QKeyEvent>
#include "roomview.h"
#include "shotgunview.h"
#include "bulletview.h"
#include "mousepicker.h"
#include "renderer.h"
#include "loader.h"
#include "texture.h"

#include "QKeyEvent"
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QTextStream>


SpaceView::SpaceView(QWidget *parent, bool isWireframe) : QOpenGLWidget(parent) {


    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);

    this->cameraView = new CameraView;
    this->isWireframe = isWireframe;
}

/**
 * Standard initializer (might still need changes)
 *
 * @brief SpaceView::initializeGL
 */
void SpaceView::initializeGL () {
    setMouseTracking(true);
    QOpenGLWidget::initializeGL();

    glClearDepth(1);
    glEnable(GL_DEPTH_TEST);;

    glShadeModel(GL_SMOOTH);

    //canvasf
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat light0_position [] = {2.2f, 2.0f, 25.3f, 0.0f};
    GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_ambient []={ 1.0, 1.0, 1.0, 1.0 };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);

    timer->start(10);
    QRect rec = QApplication::desktop()->screenGeometry();
    QCursor::setPos(rec.width()/2, rec.height()/2);

    //Init models with textures & logic
    this->roomView = new RoomView(0,0,0,  50,20,50,  255.0f,192.0f,203.0f);
    this->shotgunView = new ShotgunView();
    this->barrelView = new BarrelView(1, QVector3D(2, 10, 2));
    this->barrelView2 = new BarrelView(2, QVector3D(-2, 0, 0));
    this->barrelView->setFalling();

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
    MousePicker *picker = new MousePicker(this->cameraView->getCamera());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //PICKING STUFF
    GLuint selectBuf[512];
    glRenderMode( GL_SELECT );
    glInitNames( );
    glPushName(0);
    glSelectBuffer( 512, selectBuf );


    //PICKING STUFF
    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );
    // remember current matrix
    GLdouble pm[16];
    glGetDoublev( GL_PROJECTION_MATRIX, pm );
    glMatrixMode( GL_PROJECTION );

    glPushMatrix( );
        glLoadIdentity();
        //this->cameraView->Draw();
        QVector2D mouseView = this->cameraView->getMousePosition();
        //this->shotgunView->draw(isWireframe);

        gluPickMatrix( mouseView[0], (viewport[3] - mouseView[1]), 5.0, 5.0, viewport ); // create picking region
        glMultMatrixd( pm ); // apply projection

        glPushName( 2 );
        this->barrelView->drawColor();
        glPopName( );
        //glPushName( 2 );
        //this->roomView->draw(isWireframe);
        //glPopName( );


    glMatrixMode( GL_PROJECTION );
    glPopMatrix( );
    glFlush();
    GLint hits = glRenderMode( GL_RENDER );

    // store current matrix
   // glRenderMode( GL_RENDER );
    glMatrixMode( GL_MODELVIEW );

    glPushMatrix( );
        glLoadIdentity();

        this->shotgunView->draw(isWireframe);
        this->cameraView->Draw();

        this->barrelView->draw(isWireframe);
       // this->roomView->draw(isWireframe);
//        if (bulletView != nullptr) {
//            bulletView->draw(isWireframe);

//        }


        QVector<float> vertices = {

            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };

        GLfloat vertices2[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };

        QVector4D color = {
                1.0f, 0.0f, 0.0f, 1.0f
        };

        GLfloat g_vertex_buffer_data[] = {
           -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           0.0f,  1.0f, 0.0f,
        };
        int indeces[] = { 0, 1, 3, 3, 1, 2 };

        ShaderStatic* shader = new ShaderStatic();
        Renderer* renderAll = new Renderer();
        Loader* loader = new Loader();

        //RawModel* wallModel = loader->loadToVAO(vertices, indeces, GL_TRIANGLES);
        //RawModel* triangle = new RawModel()

        //Entity* wallEntity = new Entity(*wallModel,  QVector3D(0, 0,0), 0,0,0 ,1);


        //wallEntity.increaseRotation(0,1,0);
//                   shader->start();
//                   //renderAll.renderTextured(wallTextured);
//                   renderAll->renderEntity(*wallEntity, *shader);
//                   //renderAll.render(wallModel);
//                   shader->stop();
                   //polygonRenderer.render(barrelModel);
        // An array of 3 vectors which represents 3 vertices

        glTranslated(2, 0, 0);

        Texture* texture = new Texture();
        QString path{QCoreApplication::applicationDirPath() + "/../../../../Dusk2/wall.jpg"};
        texture->initTexture(path);



        shader->start();
        shader->setColor(color);
        renderAll->render(vertices);
        shader->stop();

        glTranslated(2, 0, 0);
        GLuint vertexbuffer;
        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
           0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
           3,                  // size
           GL_FLOAT,           // type
           GL_FALSE,           // normalized?
           0,                  // stride
           (void*)0            // array buffer offset
        );
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);


    glMatrixMode( GL_MODELVIEW );
    glPopMatrix( );

    glFlush();
    glFinish();

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Read the pixel at the center of the screen.
    // You can also use glfwGetMousePos().
    // Ultra-mega-over slow too, even for 1 pixel,
    // because the framebuffer is on the GPU.
    unsigned char data[4];
    QRect rec = QApplication::desktop()->screenGeometry();

    glReadPixels(rec.width()/2, rec.height()/2,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);

    this->pickedID =
        data[0] +
        data[1] * 256 +
        data[2] * 256*256;

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
    this->bulletView = new BulletView(cameraView->getCameraLocation(), cameraView->getCameraLookingDirection());
    QTextStream out(stdout);
//    dbool test = this->pickedID == *getUniqueColor(2);
    QString test = QString::number(this->pickedID);
    out << test + " " + QString::number(*getUniqueColor(2)) + "\n";

}

int* SpaceView::getUniqueColor(int i) {
    // Convert "i", the integer mesh ID, into an RGB color
    int r = (i & 0x000000FF) >>  0;
    int g = (i & 0x0000FF00) >>  8;
    int b = (i & 0x00FF0000) >> 16;

    int color= r + g * 256 + b * 256 * 256;
    return &color;
}
