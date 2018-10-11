TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += release static

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3 -march=native -funroll-loops
QMAKE_CFLAGS_RELEASE   += -O3

SOURCES += \
        main.cpp \
    des.cpp

HEADERS += \
    des.h \
    progress.hpp \
    timer.hpp
