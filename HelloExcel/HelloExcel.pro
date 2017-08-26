#--------------------------------------------------------------------
# HelloExcel.pro
#
#
# MIT License
# Copyright (c) 2017, j2doll (https://github.com/j2doll)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#--------------------------------------------------------------------

QT += core
TARGET = HelloExcel
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

# set include & libs path for your own test environment

# case : Qt5 & MingW(gcc) & QtCreator & Windows
win32-g++ 
{
    INCLUDEPATH += "../QtXlsxWriter-Static/QtXlsxWriter-Static/include"
    CONFIG(debug, debug|release) {
        LIBS += -L"../build-QtXlsxWriter-Static-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug"
        # DESTDIR = build/debug
    } else {
        LIBS += -L"../build-QtXlsxWriter-Static-Desktop_Qt_5_9_1_MinGW_32bit-Release/release"
        # DESTDIR = build/release
    }
}

# case : Qt5 & Linux & gcc
linux-g++ 
{
    INCLUDEPATH += "../QtXlsxWriter-Static/include"
    LIBS += -L"../QtXlsxWriter-Static/"
}

LIBS += -lQtXlsxWriter-Static

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp





