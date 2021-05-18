#include "shootapplication.h"
#include <QSurfaceFormat>

ShootApplication::ShootApplication(QWidget *parent) : QMainWindow {parent} {
//    QSurfaceFormat format;
//    format.setDepthBufferSize(24);
//    format.setStencilBufferSize(8);
//    format.setVersion(4, 1);
//    format.setProfile(QSurfaceFormat::CoreProfile);
//    format.setOption(QSurfaceFormat::DeprecatedFunctions);
//    view.makeCurrent();
//    QSurfaceFormat::setDefaultFormat(format);
//    view.setFormat(format);

    setWindowTitle("SHOOT");
    resize(640,480); //getallen van Frank (breedte en hoogte)
    setWindowState(Qt::WindowFullScreen); //set full screen
    setCentralWidget(&view);

}
