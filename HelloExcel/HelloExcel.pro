################################################################################
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

include($$PWD/UseQXlsx.pri) 

################################################################################
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

################################################################################
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

################################################################################
# source code

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
worksheetoperations.cpp \
readStyle.cpp
