#ifndef SHOOTAPPLICATION_H
#define SHOOTAPPLICATION_H
#include <QMainWindow>
#include "spaceview.h"

class ShootApplication :  public QMainWindow
{
public:
    ShootApplication(QWidget *parent=0);

private:
    SpaceView view;
};

#endif // SHOOTAPPLICATION_H
