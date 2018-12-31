#-------------------------------------------------
# Copycat.pro
#-------------------------------------------------
# QXlsx, MIT License, https://github.com/j2doll/QXlsx
#-------------------------------------------------
# QtXlsx, MIT License, https://github.com/dbzhang800/QtXlsxWriter
# Qt-Table-Printer, BSD 3-Clause License, https://github.com/T0ny0/Qt-Table-Printer
# Qt, LGPL v3 or Commercial License, https://www.qt.io
#-------------------------------------------------

TARGET = Copycat
TEMPLATE = app

QT += core
QT += gui
QT += widgets
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# NOTE: You can fix value of QXlsx path of source code.
#  QXLSX_PARENTPATH=./
#  QXLSX_HEADERPATH=./header/
#  QXLSX_SOURCEPATH=./source/
include(../QXlsx/QXlsx.pri)

INCLUDEPATH += \
./Qt-Table-Printer

HEADERS += \
./Qt-Table-Printer/tableprinter.h \
MainWindow.h \
XlsxTab.h \
xlsx.h \
CopycatTableModel.h

SOURCES += \
./Qt-Table-Printer/tableprinter.cpp \
main.cpp \
MainWindow.cpp \
XlsxTab.cpp \
CopycatTableModel.cpp

FORMS += \
MainWindow.ui

RESOURCES += \
resources.qrc

