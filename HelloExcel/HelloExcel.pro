#
# HelloExcel.pro
#
# QXlsx https://github.com/j2doll/QXlsx
#
# GPL License v3 https://www.gnu.org/licenses/gpl-3.0.en.html
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 
 
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
    INCLUDEPATH += "../QXlsx/QXlsx/header"

    CONFIG(debug, debug|release) {
        contains(QT_VERSION, 5.6.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.7.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.7.1) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.8.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_8_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.9.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_0_MinGW_32bit-Debug/debug"
        }
        contains(QT_VERSION, 5.9.1) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug"
        }
    } else {
        contains(QT_VERSION, 5.6.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.7.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.7.1) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.8.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_8_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.9.0) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_0_MinGW_32bit-Release/release"
        }
        contains(QT_VERSION, 5.9.1) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_1_MinGW_32bit-Release/release"
        }
    }
}

# case : Qt5 & Linux & gcc
linux-g++ 
{
    INCLUDEPATH += "../QXlsx/header"
    LIBS += -L"../QXlsx/"
}

# case : Qt5 & Visual Studio(VC++) & Windows

win32-msvc2012
{
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug" 
    } else {
        LIBS += -L"../QXlsx/release" 
    }
}

win32-msvc2013
{
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug" 
    } else {
        LIBS += -L"../QXlsx/release" 
    }
}

win32-msvc2015
{
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug" 
    } else {
        LIBS += -L"../QXlsx/release" 
    }
}

win32-msvc2017
{
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug" 
    } else {
        LIBS += -L"../QXlsx/release" 
    }
}

# case : Qt5 & XCode(gcc) & MAC OS

mac
{
    
}

# link QXlsx library
LIBS += -lQXlsx

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






