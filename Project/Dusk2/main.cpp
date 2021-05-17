#include "shootapplication.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,1);
   // PrintProfile(format); // Prints out the QSurfaceFormat::OpenGLContextProfile
    ShootApplication w;
    w.show();
    return a.exec();
}
