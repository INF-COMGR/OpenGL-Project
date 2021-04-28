#ifndef SPACEAPPLICATION_H
#define SPACEAPPLICATION_H
#include <QMainWindow>
#include "spaceview.h"

class SpaceApplication : public QMainWindow
{
    Q_OBJECT
public:
    SpaceApplication(QWidget *parent = nullptr);

private:
    SpaceView view;
};

#endif // SPACEAPPLICATION_H
