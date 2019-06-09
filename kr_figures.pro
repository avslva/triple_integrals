#-------------------------------------------------
#
# Project created by QtCreator 2018-05-21T14:51:31
#
#-------------------------------------------------

QT   += core gui
QT   += opengl

LIBS += -lopengl32
LIBS += -lglut32
LIBS += -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kr_figures
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    object3d.cpp \
    group3d.cpp \
    camera3d.cpp \
    mainwindow.cpp \
    largewidget.cpp \
    addformula.cpp \
    shape.cpp \
    tetraider.cpp \
    line.cpp \
    point.cpp \
    plane.cpp \
    sectionwindow.cpp \
    sectionwidget.cpp

HEADERS += \
        widget.h \
    object3d.h \
    transformational.h \
    group3d.h \
    camera3d.h \
    mainwindow.h \
    largewidget.h \
    addformula.h \
    shape.h \
    tetraider.h \
    line.h \
    point.h \
    plane.h \
    sectionwindow.h \
    sectionwidget.h

DISTFILES +=

RESOURCES += \
    shaders.qrc

FORMS += \
    mainwindow.ui \
    largewidget.ui \
    addformula.ui \
    sectionwindow.ui
