#include "application.h"

Application::Application(std::string title, int height, int width)
{
    this->setWindowTitle(title.data());
    resize(width, height);
    setWindowState(Qt::WindowFullScreen);
    initView();
}

void Application::initView()
{
    setCentralWidget(&view);
    view.changeCam(2, 2, 25, 0, 0, -1, 0, 1, 0);
}
