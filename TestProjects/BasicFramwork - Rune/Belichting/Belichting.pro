QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    cameraview.cpp \
    globe.cpp \
    globeview.cpp \
    light.cpp \
    lightview.cpp \
    main.cpp \
    mainwindow.cpp \
    space.cpp \
    spaceapplication.cpp \
    spaceview.cpp

HEADERS += \
    camera.h \
    cameraview.h \
    globe.h \
    globeview.h \
    light.h \
    lightview.h \
    mainwindow.h \
    space.h \
    spaceapplication.h \
    spaceview.h \
    util.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
