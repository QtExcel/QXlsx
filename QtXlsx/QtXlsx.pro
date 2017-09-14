######################################################################
#
# QtXlsxWriter static library 
#
# https://github.com/j2doll/QtXlsxWriter-Static
#
# MIT License
#
# Copyright (c) 2017-, j2doll (https://github.com/j2doll)
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
######################################################################

TARGET = QtXlsxWriter-Static
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

win32-g++
{
    INCLUDEPATH += header/win32-gcc # mingw32
}

win32-msvc2013
{
    INCLUDEPATH += header/msvc2013 # visual c++ 2013
}

win32-msvc2015
{
    INCLUDEPATH += header/msvc2015 # visual c++ 2015
}

win32-msvc2017
{
    INCLUDEPATH += header/msvc2017 # visual c++ 2017
}

unix 
{
   INCLUDEPATH += header/unix-gcc
   !contains(QT_ARCH, x86_64){
       LIB=lib32
       message("compiling for 32bit linux system")
    } else {
       LIB=lib64
       message("compiling for 64bit linux system")
   }
    # target.path = /usr/lib
    # INSTALLS += target
}

mac 
{
    INCLUDEPATH += header/mac
}

######################################################################

INCLUDEPATH += header

HEADERS += \
header/xlsxabstractooxmlfile.h \ 
header/xlsxabstractooxmlfile_p.h \ 
header/xlsxabstractsheet.h \ 
header/xlsxabstractsheet_p.h \ 
header/xlsxcell.h \ 
header/xlsxcellformula.h \ 
header/xlsxcellformula_p.h \ 
header/xlsxcellrange.h \ 
header/xlsxcellreference.h \ 
header/xlsxcell_p.h \ 
header/xlsxchart.h \ 
header/xlsxchartsheet.h \ 
header/xlsxchartsheet_p.h \ 
header/xlsxchart_p.h \ 
header/xlsxcolor_p.h \ 
header/xlsxconditionalformatting.h \ 
header/xlsxconditionalformatting_p.h \ 
header/xlsxcontenttypes_p.h \ 
header/xlsxdatavalidation.h \ 
header/xlsxdatavalidation_p.h \ 
header/xlsxdocpropsapp_p.h \ 
header/xlsxdocpropscore_p.h \ 
header/xlsxdocument.h \ 
header/xlsxdocument_p.h \ 
header/xlsxdrawinganchor_p.h \ 
header/xlsxdrawing_p.h \ 
header/xlsxformat.h \ 
header/xlsxformat_p.h \ 
header/xlsxglobal.h \ 
header/xlsxmediafile_p.h \ 
header/xlsxnumformatparser_p.h \ 
header/xlsxrelationships_p.h \ 
header/xlsxrichstring.h \ 
header/xlsxrichstring_p.h \ 
header/xlsxsharedstrings_p.h \ 
header/xlsxsimpleooxmlfile_p.h \ 
header/xlsxstyles_p.h \ 
header/xlsxtheme_p.h \ 
header/xlsxutility_p.h \ 
header/xlsxworkbook.h \ 
header/xlsxworkbook_p.h \ 
header/xlsxworksheet.h \ 
header/xlsxworksheet_p.h \ 
header/xlsxzipreader_p.h \ 
header/xlsxzipwriter_p.h

SOURCES += \
source/xlsxabstractooxmlfile.cpp \
source/xlsxabstractsheet.cpp \
source/xlsxcell.cpp \
source/xlsxcellformula.cpp \
source/xlsxcellrange.cpp \
source/xlsxcellreference.cpp \
source/xlsxchart.cpp \
source/xlsxchartsheet.cpp \
source/xlsxcolor.cpp \
source/xlsxconditionalformatting.cpp \
source/xlsxcontenttypes.cpp \
source/xlsxdatavalidation.cpp \
source/xlsxdocpropsapp.cpp \
source/xlsxdocpropscore.cpp \
source/xlsxdocument.cpp \
source/xlsxdrawing.cpp \
source/xlsxdrawinganchor.cpp \
source/xlsxformat.cpp \
source/xlsxmediafile.cpp \
source/xlsxnumformatparser.cpp \
source/xlsxrelationships.cpp \
source/xlsxrichstring.cpp \
source/xlsxsharedstrings.cpp \
source/xlsxsimpleooxmlfile.cpp \
source/xlsxstyles.cpp \
source/xlsxtheme.cpp \
source/xlsxutility.cpp \
source/xlsxworkbook.cpp \
source/xlsxworksheet.cpp \
source/xlsxzipreader.cpp \
source/xlsxzipwriter.cpp


