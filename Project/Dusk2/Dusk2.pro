QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barrel.cpp \
    barrelview.cpp \
    bullet.cpp \
    bulletview.cpp \
    camera.cpp \
    cameraview.cpp \
    floor.cpp \
    floorview.cpp \
    hitbox.cpp \
    main.cpp \
    room.cpp \
    roomview.cpp \
    shootapplication.cpp \
    shotgun.cpp \
    shotgunview.cpp \
    spaceview.cpp \
    wall.cpp \
    wallview.cpp

HEADERS += \
    barrel.h \
    barrelview.h \
    bullet.h \
    bulletview.h \
    camera.h \
    cameraview.h \
    floor.h \
    floorview.h \
    hitbox.h \
    room.h \
    roomview.h \
    shootapplication.h \
    shotgun.h \
    shotgunview.h \
    spaceview.h \
    stb_image.h \
    util.h \
    wall.h \
    wallview.h

FORMS += \
    shootapplication.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
