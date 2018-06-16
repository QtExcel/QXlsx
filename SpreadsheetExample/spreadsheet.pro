#
# spreadsheet.pro 
#
# main code from qt example. https://www.qt.io (c) The Qt Company Ltd.
# BSD License
#
# Some code is fixed by j2doll.
#

QT += widgets

qtHaveModule(printsupport): QT += printsupport
#unix:qtHaveModule(dbus): QT += dbus widgets

QXLSX_PARENTPATH=../QXlsx/
QXLSX_HEADERPATH=../QXlsx/header/
QXLSX_SOURCEPATH=../QXlsx/source/
include(../QXlsx/QXlsx.pri)

HEADERS += \
printview.h \
spreadsheet.h \
spreadsheetdelegate.h \
spreadsheetitem.h

SOURCES += \
main.cpp \
printview.cpp \
spreadsheet.cpp \
spreadsheetdelegate.cpp \
spreadsheetitem.cpp

RESOURCES += \
spreadsheet.qrc


