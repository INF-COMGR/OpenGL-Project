#include "shootapplication.h"

#include <QApplication>
#include <QOpenGLContext>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    ShootApplication w;
    w.show();
    return a.exec();
}
