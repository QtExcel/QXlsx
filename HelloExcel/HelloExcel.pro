#--------------------------------------------------------------------
#
# HelloExcel.pro
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
#
#--------------------------------------------------------------------

QT += core
QT += gui
TARGET = HelloExcel
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

#--------------------------------------------------------------------
# set include & libs path for your own test environment

# case : Qt5 & MingW(gcc) & QtCreator & Windows
win32-g++ 
{
    INCLUDEPATH += "../QtXlsx/QtXlsx/header"

    CONFIG(debug, debug|release) {
        contains(QT_VERSION, 5.6.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.7.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.7.1) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.8.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_8_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.9.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_9_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.9.1) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug"
        }
    } else {
        contains(QT_VERSION, 5.6.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.7.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.7.1) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.8.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_8_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.9.0) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_9_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.9.1) {
            LIBS += -L"../build-QtXlsx-Desktop_Qt_5_9_1_MinGW_32bit-Release/release"
        }
    }
}

# case : Qt5 & Linux & gcc
linux-g++ 
{
    INCLUDEPATH += "../QtXlsx/header"
    LIBS += -L"../QtXlsx/"
}

# case : Qt5 & Visual Studio(VC++) & Windows

win32-msvc2013
{
    CONFIG(debug, debug|release) {
        # LIBS += -L"" # debug lib 
    } else {
        # LIBS += -L"" $ release lib 
    }
}

win32-msvc2015
{
    CONFIG(debug, debug|release) {
        # LIBS += -L"" # debug lib 
    } else {
        # LIBS += -L"" $ release lib 
    }
}

# case : Qt5 & XCode(gcc) & MAC OS

mac
{
    
}

# link QtXlsx library
LIBS += -lQtXlsx

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
calendar.cpp \
chart.cpp \
chartsheet.cpp \
datavalidation.cpp \
definename.cpp \
demo.cpp \
documentproperty.cpp \
extractdata.cpp \
formulas.cpp \
hello.cpp \
hyperlinks.cpp \
image.cpp \
main.cpp \
mergecells.cpp \
numberformat.cpp \
richtext.cpp \
rowcolumn.cpp \
style.cpp \
worksheetoperations.cpp






