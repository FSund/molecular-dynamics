include(../defaults.pri)

CONFIG   += console
CONFIG   -= app_bundle
CONFIG   -= qt

TEMPLATE = lib

TARGET = myapp

SOURCES += \
    atom.cpp \
    system.cpp \
    vector3d.cpp \
    integrator.cpp \
    force.cpp \
    systemgenerator.cpp

HEADERS += \
    atom.h \
    system.h \
    vector3d.h \
    box.h \
    integrator.h \
    force.h \
    systemgenerator.h
