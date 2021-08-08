# QMake Build file
CFLAGS += -g -fpermissive

QMAKE_LFLAGS_X86_64 = -arch x86_64

QMAKE_CFLAGS_X86_64 = -arch x86_64
QMAKE_CXXFLAGS_X86_64 = -arch x86_64

QMAKE_CFLAGS_RELEASE += -g \
    $$BDDFLAGS
QMAKE_CXXFLAGS_RELEASE += -g -std=c++17 \
    $$BDDFLAGS
QMAKE_CFLAGS_DEBUG += -g -Wall -Wextra \
    $$BDDFLAGS
QMAKE_CXXFLAGS_DEBUG += -g -Wall -Wextra -std=c++17 \
    $$BDDFLAGS

TEMPLATE = app \
    console
CONFIG += release
CONFIG -= app_bundle
CONFIG -= qt
HEADERS += 

SOURCES += main.cpp ../../lib/picosat-965/picosat.c

TARGET = enumerator
INCLUDEPATH = ../../lib/picosat-965

LIBS += -static 

PKGCONFIG += 
QT -= gui \
    core
