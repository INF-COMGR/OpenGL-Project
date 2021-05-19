#include "spaceview.h"
#include "util.h"
#include "cameraview.h"
#include "barrelview.h"
#include <QKeyEvent>
#include "roomview.h"
#include "shotgunview.h"
#include "bulletview.h"
#include "hitbox.h"
#include "button.h"
#include "wallview.h"
#include "cube.h"
#include "instancegrass.h"
#include "animationview.h"
#include "QKeyEvent"
#include <QApplication>
#include <QCursor>
#include <QDesktopWidget>
#include <QTextStream>
#include <Qt3DRender/QShaderProgram>

#include <QOpenGLShaderProgram>



SpaceView::SpaceView(QWidget *parent, bool isWireframe) : QOpenGLWidget(parent) {
//    QSurfaceFormat format;
//    format.setVersion(3,3);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    format.setOption(QSurfaceFormat::DeprecatedFunctions);
//    this->setFormat(format);
//    QSurfaceFormat format;
//    format.setDepthBufferSize( 24 );
//    format.setMajorVersion( 4 );
//    format.setMinorVersion( 3 );
//    format.setSamples( 4 );
//    format.setProfile( QSurfaceFormat::CoreProfile );
//    format.setOption(QSurfaceFormat::DeprecatedFunctions);
//    setFormat( format );
//    create();


    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(update()) );

    setFocusPolicy(Qt::StrongFocus);

    this->cameraView = new CameraView;
    this->isWireframe = isWireframe;

    scoreLabel = new QLabel("TEST", this);
    pickingLabel = new QLabel("\npicking output: ", this);
    explanationLabel = new QLabel("\n\nUse your mouse to move and click to shoot.\nShoot all the barrels to win!\n W - toggle wireframe | F - toggle noclip \nTo reset the game, look at the North and press R (usage off picking)", this);
    this->bulletView = nullptr;
    pickingBlockGiveUp = new QLabel("\n\n\n\n\n\nTo give up the game, place the red block in your bottom left corner and press 'G'.", this);
    pickingBlockGiveUp = new QLabel("\n\n\n\n\n\n\nAnother way to restart the game is to place the green block in your bottom left corner and press 'T'.", this);

    shotGunSound = new QSoundEffect(this);
    shotGunSound->setSource(QUrl::fromLocalFile(":/:/shotgunsound.wav"));
    shotGunSound->setLoopCount(1);
    shotGunSound->setVolume(0.05f);

    winningSound = new QSoundEffect(this);
    winningSound->setSource(QUrl::fromLocalFile(":/:/winningsound.wav"));
    winningSound->setLoopCount(1);
    winningSound->setVolume(0.2f);

    losingSound = new QSoundEffect(this);
    losingSound->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/../../../../Dusk2/lose.wav"));
    losingSound->setLoopCount(1);
    losingSound->setVolume(0.2f);
}

/**
 * Standard initializer (might still need changes)
 *
 * @brief SpaceView::initializeGL
 */
void SpaceView::initBarrels()
{
    this->littleWall1 = new Cube(25,0,10, 26,7,30);
    this->littleWall2 = new Cube(0,0,30, 20,4,29.9f);
    this->barrels.append(new BarrelView(1, QVector3D(2, 7, 2)));        //small barrel (size 1) on top of big barrel begin view
    this->barrels.append(new BarrelView(2, QVector3D(2, 4, 2)));        //big barrel (size 2) under small barrel begin view
    this->barrels.append(new BarrelView(5, QVector3D(10, 10, 10)));     //giant barrel (size 5) to the side
    this->barrels.append(new BarrelView(3, QVector3D(10, 30, 10)));     //small barrel 1 (size 3) on top of giant barrel
    this->barrels.append(new BarrelView(2, QVector3D(10, 40, 10)));     //small barrel 2 (size 2) on top of giant barrel
    this->barrels.append(new BarrelView(1, QVector3D(10, 50, 10)));     //small barrel 3 (size 1) on top of giant barrel

    this->barrels.append(new BarrelView(2, QVector3D(35, 40, 20)));
    this->barrels.append(new BarrelView(2, QVector3D(20, 35, 30)));

    this->barrels.append(new BarrelView(1, QVector3D(35, 10, 25)));
    this->barrels.append(new BarrelView(1, QVector3D(25, 15, 35)));

    this->barrels.append(new BarrelView(3, QVector3D(25, 20, 20)));
    this->barrels.append(new BarrelView(5, QVector3D(27, 30, 20)));
    this->barrels.append(new BarrelView(3, QVector3D(30, 40, 20)));

    this->barrels.append(new BarrelView(3, QVector3D(10, 20, 25)));
    this->barrels.append(new BarrelView(3, QVector3D(12, 30, 25)));
    this->barrels.append(new BarrelView(3, QVector3D(14, 40, 25)));

    this->barrels.append(new BarrelView(4, QVector3D(40, 30, 40)));
    this->barrels.append(new BarrelView(3, QVector3D(35, 30, 40)));
    this->barrels.append(new BarrelView(2, QVector3D(30, 30, 40)));

    this->barrels.append(new BarrelView(10, QVector3D(40, 0, 10)));
    this->barrels.append(new BarrelView(5, QVector3D(5, 2, 35)));
    this->barrels.append(new BarrelView(2, QVector3D(10, 5, 40)));

    for(int i = 0; i < barrels.length(); ++i) {
        barrels[i]->setFalling();
        barrels[i]->addHitBox(littleWall1->getHitbox());
        barrels[i]->addHitBox(littleWall2->getHitbox());
        for(int j = 0; j < barrels.length(); ++j) {
            if (i != j)
                barrels[i]->addHitBox(barrels[j]->getHitBox());
        }
        QVector<HitBox*> roomHitboxes = roomView->getHitBoxes();
        for (int i = 0; i < roomHitboxes.length(); ++i) {
            barrels[i]->addHitBox(roomHitboxes[i]);
        }
    }
}

void SpaceView::initializeGL () {
    setMouseTracking(true);
    QOpenGLWidget::initializeGL();

    glShadeModel(GL_SMOOTH);

    //canvasf
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

    // Place light
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    GLfloat light0_position [] = {0.2f, 1.0f, 0.3f, 0.0f};
    GLfloat light_diffuse []={ 1.01f, 1.01f, 1.01f, 1.0f };
    GLfloat light_ambient []={ 1.01f, 1.01f, 1.01f, 1.0f };
    glLightfv ( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv ( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);

    timer->start(FPS_COUNT);
    QRect rec = QApplication::desktop()->screenGeometry();
    QCursor::setPos(rec.width()/2, rec.height()/2);

    //Init models with textures & logic
    this->roomView = new RoomView(0,0,0,  50,20,50,  255.0f,192.0f,203.0f);

    restartButton = new button(QVector4D{0.0,1.0,0.0,1.0}, 2, 1, 20);
    giveUpButton = new button(QVector4D{1.0,0.0,0.0,1.0}, 2, 3, 20);

    this->shotgunView = new ShotgunView();
    QVector<QVector2D> texCoords1 = QVector<QVector2D>{QVector2D(1, 1), QVector2D(0, 1), QVector2D(1, 0), QVector2D(2, 0)};
    this->animationView = new AnimationView(2, QVector3D(10, 0, 3), "/88e20d896a9dd096579be10db88496f1-0/88e20d896a9dd096579be10db88496f1-", 53, texCoords1);
    QVector<QVector2D> texCoords2 = QVector<QVector2D>{QVector2D(1, 1), QVector2D(0, 1), QVector2D(1, 0), QVector2D(0, 0)};
    this->animationView2 = new AnimationView(4, QVector3D(15, 0, 3), "/1pX9-0/1pX9-", 46, texCoords2);

    initBarrels();
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
    if (!gotAllBarrels() && !gaveUp && BEGIN_SCORE - penalty > 0) {
        penalty += 1;
        if (penalty % 10 == 0) {
            scoreLabel->setText("current score: "+QString::number(BEGIN_SCORE-penalty));
            scoreLabel->adjustSize();
        }
    } else if (gaveUp) {
        scoreLabel->setText("FINAL SCORE: You gave up...");
        scoreLabel->adjustSize();
    } else if (BEGIN_SCORE - penalty <= 0) {
        this->lose();
        scoreLabel->setText("You lost the game.");
        scoreLabel->adjustSize();
    }
    else {
        scoreLabel->setText("FINAL SCORE: "+QString::number(BEGIN_SCORE-penalty));
        scoreLabel->adjustSize();
    }
}

void SpaceView::paintGL () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();


    updateScore();

    QTextStream out(stdout);
    //out << QString::number(picking->pick());
    pickingLabel->setText("\npicking output: "+QString::number(cameraView->pick()));
    pickingLabel->adjustSize();

    // store current matrix
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix( );
 /*----------------------------Trying to make headlight---------------------------------------*/
//        glPushMatrix();
//            glLoadIdentity();

//            const GLfloat pos[] = { 0., 1., 0., 1. };
//            GLfloat light_diffuse []={ 1.0, 1.0, 1.0, 1.0 };
//            GLfloat light_ambient []={ 1.0, 1.0, 1.0, 1.0 };
//            glLightfv( GL_LIGHT1, GL_POSITION, pos );
//            glLightfv ( GL_LIGHT1, GL_DIFFUSE, light_diffuse );
//            glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
//            glEnable( GL_LIGHT1 );
//        glPopMatrix();
/*--------------------------------------------------------------------------------------------*/
        this->shotgunView->draw(isWireframe);
        this->cameraView->Draw();
        for (int i = 0; i < barrels.length(); ++i)
            barrels[i]->draw(isWireframe);
        this->roomView->draw(isWireframe);
        this->littleWall1->draw(isWireframe);
        this->littleWall2->draw(isWireframe);
        if (bulletView != nullptr)
            bulletView->draw(isWireframe);

        restartButton->draw(isWireframe);
        giveUpButton->draw(isWireframe);

        animationView->draw(isWireframe);
        animationView2->draw(isWireframe);
        //InstanceGrass* grass = new InstanceGrass();
        //grass->draw();

    glPopMatrix( );
}

void SpaceView::keyPressEvent(QKeyEvent * e) {
    if (e->key() == Qt::Key::Key_W)
        this->isWireframe = this->isWireframe ? false : true;
    if (e->key() == Qt::Key::Key_R && pickingLabel->text() == "\npicking output: 1")
        this->restart();

    cameraView->keyPressEvent(e);
    this->handlePicking(e);

}

void SpaceView::restart() {
    gaveUp = false;
    penalty = 0;
    this->barrels.clear();
    initBarrels();
    winningSoundPlayed = false;
}

void SpaceView::mouseMoveEvent(QMouseEvent *e) {
    cameraView->mouseMouveEvent(e);
}

/* https://stackoverflow.com/questions/8841422/glreadpixels-data-argument-usage */
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
    this->bulletView->addHitBox(littleWall1->getHitbox());
    this->bulletView->addHitBox(littleWall2->getHitbox());

}

void SpaceView::handlePicking(QKeyEvent* e) {
    unsigned char pixels[ 1 * 1 * 3 ] = { 0 };
    glReadPixels(0, 0, 1, 1,GL_RGB, GL_UNSIGNED_BYTE, pixels);
    GLubyte R = static_cast<int> (pixels[0]);
    GLubyte G = static_cast<int> (pixels[1]);

    if (G == 255 && e->key() == Qt::Key_T)
        this->restart();
    if (R == 255 &&  e->key() == Qt::Key_G) {
        this->gaveUp = true;
        this->lose();
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

void SpaceView::lose() {
    if (!losingSoundPlayed)
        losingSound->play();
    losingSoundPlayed = true;
}




