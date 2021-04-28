#include "mainwindow.h"

#include <QApplication>
#include "shootapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShootApplication w;
    w.show();
    return a.exec();
}
