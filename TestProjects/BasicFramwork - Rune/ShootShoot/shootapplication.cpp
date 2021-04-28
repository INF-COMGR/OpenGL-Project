#include "shootapplication.h"

ShootApplication::ShootApplication(QWidget *parent) : QMainWindow {parent} {
    setWindowTitle("SHOOT");
    resize(640,480); //getallen van Frank (breedte en hoogte)
    setWindowState(Qt::WindowMaximized); //set full screen
    setCentralWidget(&view);

}
