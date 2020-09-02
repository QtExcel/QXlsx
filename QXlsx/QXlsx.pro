# QXlsx.pro

TARGET = QXlsx
TEMPLATE = lib
CONFIG += create_prl create_pc
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

isEmpty(DESTDIR): DESTDIR = $$OUT_PWD/../bin

isEmpty(PREFIX) : !isEmpty(INSTALL_ROOT) : PREFIX=$$INSTALL_ROOT
isEmpty(PREFIX) {
    qnx : PREFIX = /tmp/$${TARGET}
    else : android : PREFIX = /.
    else : PREFIX = $$OUT_PWD/../install
}

!static : !staticlib : DEFINES *= BUILD_SHARED_LIBS QXlsx_EXPORTS

QXLSX_PARENTPATH=$$PWD/
QXLSX_HEADERPATH=$$PWD/header/
QXLSX_SOURCEPATH=$$PWD/source/
include($$PWD/QXlsx.pri)

header_files.target = header_files
header_files.files = $${INSTALL_HEADER_FILES}
header_files.path = $$PREFIX/include/$${TARGET}
target.path = $$PREFIX/lib
INSTALLS += target header_files

OTHER_FILES *= CMakeLists.txt
