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
    math/bskeleton.cpp \
    modele/urbanisation/ville.cpp \
    modele/urbanisation/route.cpp

HEADERS += \
    geometrie/box.h \
    geometrie/vector3d.h \
    modele/terrain/terrain.h \
    modele/terrain/terraintab.h \
    math/interpolation.h \
    math/bskeleton.h \
    modele/urbanisation/ville.h \
    modele/urbanisation/route.h

