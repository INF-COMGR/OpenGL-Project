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
}
