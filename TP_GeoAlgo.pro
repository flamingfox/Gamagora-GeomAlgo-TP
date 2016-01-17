TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT += gui
QT += opengl
LIBS += -lopengl32 -lglu32

SOURCES += main.cpp \
    OpenGL/myglwidget.cpp \
    OpenGL/mywindow.cpp \
    geometrie/vector2d.cpp \
    geometrie/unionconvex.cpp \
    geometrie/convexe2d.cpp \
    geometrie/polygone.cpp \
    geometrie/grahamconvex.cpp

HEADERS += OpenGL/myglwidget.h \
    OpenGL/mywindow.h \
    geometrie/vector2d.h \
    geometrie/unionconvex.h \
    geometrie/convexe2d.h \
    geometrie/polygone.h \
    geometrie/grahamconvex.h

