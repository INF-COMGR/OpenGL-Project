#include "mainwindow.h"
#include "spaceapplication.h".h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpaceApplication w;
    a.setActiveWindow(&w);
    w.show();
    return a.exec();
}
