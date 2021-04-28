#include "lightview.h"
#include <QOpenGLWidget>

#include "util.h"

LightView::LightView(float posX, float posY, float posZ, float pos, float diff1, float diff2, float diff3, float diff4) {
    light = new Light(posX, posY, posZ, pos, diff1, diff2, diff3, diff4);
}

void LightView::Draw(unsigned long lighting, unsigned long light, unsigned long position, unsigned long diffusion) {
    glEnable( lighting );
    glEnable( light );
    QVector<float> positions = this->light->getPosition();
    QVector<float> diffusions = this->light->getDiffusion();

    GLfloat light_position[] = {positions[0], positions[1], positions[2], positions[3]};
    GLfloat light_diffusion[] = {diffusions[0],diffusions[1],diffusions[2],diffusions[3]};
    glLightfv( lighting, position, light_position );
    glLightfv( light, diffusion, light_diffusion );
}

void LightView::LightUpdate(QKeyEvent* e) {
//    if(e->key() == Qt::Key_Up)
//        //camera->moveForward();

//    if(e->key() == Qt::Key_Down)
//        //camera->moveBackward();

//    if(e->key() == Qt::Key_Left)
//        //camera->Left();

//    if(e->key() == Qt::Key_Right)
//        //camera->Right();


}
