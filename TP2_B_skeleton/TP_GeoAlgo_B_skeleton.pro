TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core
QT += gui
QT += opengl
LIBS += -lopengl32 -lglu32

SOURCES += main.cpp \
    geometrie/box.cpp \
    geometrie/vector3d.cpp \
    modele/terrain/terrain.cpp \
    modele/terrain/terraintab.cpp \
    math/interpolation.cpp \
    ville.cpp

HEADERS += \
    geometrie/box.h \
    geometrie/vector3d.h \
    modele/terrain/terrain.h \
    modele/terrain/terraintab.h \
    math/interpolation.h \
    ville.h

