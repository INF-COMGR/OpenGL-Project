#include "animationview.h"
#include "animation.h"
#include <QVector3D>
#include <QVector2D>
#include "util.h"

AnimationView::AnimationView(int size, QVector3D location, QString name, int frameAmount, QVector<QVector2D> texCoords, float ratio, int waitTime):
    texCoords{texCoords}, RATIO{ratio}
{
    animation = new Animation(size, location, name, frameAmount, waitTime);
}

void AnimationView::draw(bool isWireframe) {
    glPushMatrix();
        float mcolor[] = { 1.0f,1.0f, 1.0f, 1.0f };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

        glEnable(GL_NORMALIZE);
        int size = animation->getSize();
        QVector3D location = animation->getLocation();
        animation->suggestNext();
        Texture* texture = animation->getTexture();
        if (!isWireframe)
            texture->bindTexture();
        glTranslated(location.x(), location.y(), location.z());
        glBegin( !isWireframe ? GL_POLYGON : GL_LINE_LOOP);
            glTexCoord2d(texCoords[0].x(), texCoords[0].y());
            glVertex3f(0, 0, 0);

            glTexCoord2d(texCoords[1].x(), texCoords[1].y());
            glVertex3f(size*RATIO, 0, 0);

            glTexCoord2d(texCoords[2].x(), texCoords[2].y());
            glVertex3f(size*RATIO, size, 0);

            glTexCoord2d(texCoords[3].x(), texCoords[3].y());
            glVertex3f(0, size, 0);
        glEnd();
        texture->unBindTexture();
    glPopMatrix();
}




