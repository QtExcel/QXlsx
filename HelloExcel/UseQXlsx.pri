################################################################################
# UseQXlsx.pri
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
LIBS += -lQXlsx # link QXlsx library

################################################################################
# set include & libs path for your own test environment

################################################################################
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
        contains(QT_VERSION, 5.9.2) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_2_MinGW_32bit-Debug/debug"
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
        contains(QT_VERSION, 5.9.2) {
            LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_2_MinGW_32bit-Release/release"
        }
    }
}

################################################################################
# case : Qt5 & Linux & gcc
linux-g++
{
    INCLUDEPATH += "../QXlsx/header"
    LIBS += -L"../QXlsx/"
}

################################################################################
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

################################################################################
# case : Qt5 & XCode(gcc) & MAC OS

mac
{

}
