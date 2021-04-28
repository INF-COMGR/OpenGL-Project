#ifndef APPLICATION_H
#define APPLICATION_H

// include files for QT
#include <QMainWindow>
#include "applicationview.h"

class Application : public QMainWindow
{
    Q_OBJECT
public:
    Application(std::string title, int height, int width);
    void initView();
private:
    ApplicationView view;
signals:

};

#endif // APPLICATION_H
