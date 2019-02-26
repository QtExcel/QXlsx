#
# WebServer.pro
#
# QXlsx   https://github.com/QtExcel/QXlsx

TARGET = WebServer
TEMPLATE = app

QT += core
QT += network
QT -= gui

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++14

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


