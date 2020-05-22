# ShowConsole.pro
 
TARGET = ShowConsole
TEMPLATE = app

QT += core

CONFIG += console
CONFIG += c++11 
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

##########################################################################
# NOTE: You can fix value of QXlsx path of source code.
#  QXLSX_PARENTPATH=./
#  QXLSX_HEADERPATH=./header/
#  QXLSX_SOURCEPATH=./source/
include(../QXlsx/QXlsx.pri)

# libfort (c)Seleznev Anton, MIT license
HEADERS += fort.hpp fort.h
SOURCES += fort.c

SOURCES += \
main.cpp
