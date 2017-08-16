#---------------------------------------------------------------------------
#
# QtXlsxWriter static library (https://github.com/j2doll/QtXlsxWriter-Static)
#
# MIT License
#
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
# test on :
#   Qt 5.9.1 (MingW/Windows 32bit), QtCreator 4.3.1
#
#---------------------------------------------------------------------------

TARGET = QtXlsxWriter-Static

TEMPLATE = lib

CONFIG += staticlib

QT += core gui gui-private

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# unix {
#    target.path = /usr/lib
#    INSTALLS += target
# }

# custom setting for compiler & system
win32-g++:INCLUDEPATH += include/win32-gcc # mingw32
win32-msvc2013:INCLUDEPATH += include/msvc2013 # visual c++ 2013
win32-msvc2015:INCLUDEPATH += include/msvc2015 # visual c++ 2015

INCLUDEPATH += include

HEADERS += \
include/xlsxdocpropscore_p.h \
include/xlsxdocpropsapp_p.h \
include/xlsxrelationships_p.h \
include/xlsxutility_p.h \
include/xlsxsharedstrings_p.h \
include/xlsxcontenttypes_p.h \
include/xlsxtheme_p.h \
include/xlsxformat.h \
include/xlsxworkbook.h \
include/xlsxstyles_p.h \
include/xlsxabstractsheet.h \
include/xlsxabstractsheet_p.h \
include/xlsxworksheet.h \
include/xlsxworksheet_p.h \
include/xlsxchartsheet.h \
include/xlsxchartsheet_p.h \
include/xlsxzipwriter_p.h \
include/xlsxworkbook_p.h \
include/xlsxformat_p.h \
include/xlsxglobal.h \
include/xlsxdrawing_p.h \
include/xlsxzipreader_p.h \
include/xlsxdocument.h \
include/xlsxdocument_p.h \
include/xlsxcell.h \
include/xlsxcell_p.h \
include/xlsxdatavalidation.h \
include/xlsxdatavalidation_p.h \
include/xlsxcellreference.h \
include/xlsxcellrange.h \
include/xlsxrichstring_p.h \
include/xlsxrichstring.h \
include/xlsxconditionalformatting.h \
include/xlsxconditionalformatting_p.h \
include/xlsxcolor_p.h \
include/xlsxnumformatparser_p.h \
include/xlsxdrawinganchor_p.h \
include/xlsxmediafile_p.h \
include/xlsxabstractooxmlfile.h \
include/xlsxabstractooxmlfile_p.h \
include/xlsxchart.h \
include/xlsxchart_p.h \
include/xlsxsimpleooxmlfile_p.h \
include/xlsxcellformula.h \
include/xlsxcellformula_p.h

SOURCES += \
source/xlsxdocpropscore.cpp \
source/xlsxdocpropsapp.cpp \
source/xlsxrelationships.cpp \
source/xlsxutility.cpp \
source/xlsxsharedstrings.cpp \
source/xlsxcontenttypes.cpp \
source/xlsxtheme.cpp \
source/xlsxformat.cpp \
source/xlsxstyles.cpp \
source/xlsxworkbook.cpp \
source/xlsxabstractsheet.cpp \
source/xlsxworksheet.cpp \
source/xlsxchartsheet.cpp \
source/xlsxzipwriter.cpp \
source/xlsxdrawing.cpp \
source/xlsxzipreader.cpp \
source/xlsxdocument.cpp \
source/xlsxcell.cpp \
source/xlsxdatavalidation.cpp \
source/xlsxcellreference.cpp \
source/xlsxcellrange.cpp \
source/xlsxrichstring.cpp \
source/xlsxconditionalformatting.cpp \
source/xlsxcolor.cpp \
source/xlsxnumformatparser.cpp \
source/xlsxdrawinganchor.cpp \
source/xlsxmediafile.cpp \
source/xlsxabstractooxmlfile.cpp \
source/xlsxchart.cpp \
source/xlsxsimpleooxmlfile.cpp \
source/xlsxcellformula.cpp

