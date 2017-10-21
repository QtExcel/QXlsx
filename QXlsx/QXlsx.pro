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

win32-g++
{
    message("compiling for win32 g++")
    INCLUDEPATH += header/win32-gcc # mingw32
}

win32-msvc2013
{
    message("compiling for visual studio 2013")
    INCLUDEPATH += header/msvc2013 # visual c++ 2013
}

win32-msvc2015
{
    message("compiling for visual studio 2015")
    INCLUDEPATH += header/msvc2015 # visual c++ 2015
}

win32-msvc2017
{
    message("compiling for visual studio 2017")
    INCLUDEPATH += header/msvc2017 # visual c++ 2017
}

unix 
{
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

mac 
{
    message("compiling for visual mac")
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


