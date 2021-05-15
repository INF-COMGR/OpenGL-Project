#ifndef LIGHT_H
#define LIGHT_H
#include <QVector3D>

class Light
{
public:
    Light(QVector3D position, QVector3D color);
private:
    QVector3D position;
    QVector3D color;

};

#endif // LIGHT_H
