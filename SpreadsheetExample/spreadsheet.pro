#
# spreadsheet.pro 
# main code from qt example. https://www.qt.io
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

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

# install
# target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/spreadsheet
# INSTALLS += target

