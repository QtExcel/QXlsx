######################################################################
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
######################################################################

TARGET = QXlsx
TEMPLATE = lib
CONFIG += staticlib
QT += core
QT += gui-private

#####################################################################
# set debug/release build environment
#
# CONFIG += debug_and_release
# release: DESTDIR = lib-release
# debug: DESTDIR = lib-debug

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

######################################################################
# custom setting for compiler & system

win32-g++ {
    message("compiling for win32 g++")
    INCLUDEPATH += header/win32-gcc 
}
win32-msvc2013 {
    message("compiling for visual studio 2013")
    INCLUDEPATH += header/msvc2013 
}
win32-msvc2015 {
    message("compiling for visual studio 2015")
    INCLUDEPATH += header/msvc2015 
}
win32-msvc2017 {
    message("compiling for visual studio 2017")
    INCLUDEPATH += header/msvc2017 
}
unix {
   !contains(QT_ARCH, x86_64){
       LIB=lib32
       message("compiling for 32bit linux system")
    } else {
       LIB=lib64
       message("compiling for 64bit linux system")
   }

   INCLUDEPATH += header/unix-gcc

    # target.path = /usr/lib
    # INSTALLS += target
}
mac {
    message("compiling for mac os")
    INCLUDEPATH += header/mac
}

######################################################################
# header and source files 

INCLUDEPATH += header

include(./QXlsx.pri)

