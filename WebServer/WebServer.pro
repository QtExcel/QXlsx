# WebServer.pro
 
TARGET = WebServer
TEMPLATE = app

QT += core
QT += network
QT -= gui

CONFIG += console
CONFIG -= app_bundle

# C++14 or higher version is required.
# CONFIG += c++14
# QMAKE_CXXFLAGS += -std=c++14
# C++17 or higher version is required.
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

macx {
    QMAKE_CXXFLAGS += -stdlib=libc++
}

# NOTE: You can fix value of QXlsx path of source code.
#  QXLSX_PARENTPATH=./
#  QXLSX_HEADERPATH=./header/
#  QXLSX_SOURCEPATH=./source/
include(../QXlsx/QXlsx.pri)

# source code

RESOURCES += \
ws.qrc

HEADERS += \
recurse.hpp \
request.hpp \
response.hpp \
context.hpp

INCLUDEPATH += .

SOURCES += \
main.cpp


