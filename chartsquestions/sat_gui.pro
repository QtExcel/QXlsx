#
# sat_gui.pro
#
# Copyright (c) 2018 edosad(github) All rights reserved.
#
# Some code is fixed by j2doll(github)

QT += core
QT += gui
QT += widgets

TARGET = sat_gui
TEMPLATE = app

# NOTE: You can fix value of QXlsx path of source code.
#  QXLSX_PARENTPATH=./
#  QXLSX_HEADERPATH=./header/
#  QXLSX_SOURCEPATH=./source/
include(../QXlsx/QXlsx.pri)

# include("D:\resin_example\sat_gui\src\xlsx\qtxlsx.pri")
# QMAKE_LFLAGS += -static -static-libgcc

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
main.cpp \
mainwindow.cpp \
sat_calc.cpp

HEADERS += \
mainwindow.h \
sat_calc.h

FORMS += \
mainwindow.ui

RESOURCES += \
test.qrc

#OTHER_FILES += \
#Chromatogram_example.txt


