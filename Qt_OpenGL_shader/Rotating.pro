#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T22:22:12
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /home/pi/NeHe_OpenGL_Qt5
TARGET = Lesson04_Rotating
INSTALLS += target
TEMPLATE = app

SOURCES += main.cpp\
        openglwindow.cpp \
    drawObj.cpp \
    include/InitShader.cpp

HEADERS  += openglwindow.h \
    drawObj.h \
    include/Angel.h \
    include/CheckError.h \
    include/mat.h \
    include/vec.h \
    tryhead.h

RESOURCES += \
    src.qrc


