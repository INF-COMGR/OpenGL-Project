#include "spaceapplication.h"

SpaceApplication::SpaceApplication(QWidget *parent) : QMainWindow {parent} {
    setWindowTitle("SPACE");
    resize(640,480); //getallen van Frank (breedte en hoogte)
    setWindowState(Qt::WindowMaximized); //set full screen
    setCentralWidget(&view);

}
