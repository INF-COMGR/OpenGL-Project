QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    animation.cpp \
    animationview.cpp \
    barrel.cpp \
    barrelview.cpp \
    bullet.cpp \
    bulletview.cpp \
    button.cpp \
    camera.cpp \
    cameraview.cpp \
    cube.cpp \
    floor.cpp \
    floorview.cpp \
    hitbox.cpp \
    instancegrass.cpp \
    main.cpp \
    picking.cpp \
    room.cpp \
    roomview.cpp \
    shootapplication.cpp \
    shotgun.cpp \
    shotgunview.cpp \
    spaceview.cpp \
    texture.cpp \
    wall.cpp \
    wallview.cpp

HEADERS += \
    Vertex.h \
    animation.h \
    animationview.h \
    barrel.h \
    barrelview.h \
    bullet.h \
    bulletview.h \
    button.h \
    camera.h \
    cameraview.h \
    cube.h \
    floor.h \
    floorview.h \
    glfw-3.3.4.bin.MACOS 2/include/GLFW/glfw3.h \
    glfw-3.3.4.bin.MACOS 2/include/GLFW/glfw3native.h \
    hitbox.h \
    instancegrass.h \
    picking.h \
    room.h \
    roomview.h \
    shootapplication.h \
    shotgun.h \
    shotgunview.h \
    spaceview.h \
    stb_image.h \
    texture.h \
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
