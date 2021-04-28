#include <QApplication>
#include "application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w("Test1", 500, 500);
    a.setActiveWindow(&w);
    w.show();
    return a.exec();
}
