########################################
# QXlsx.pri
########################################

QT += core
QT += gui-private

# TODO: Define your C++ version. c++14, c++17, etc.
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

isEmpty(QXLSX_PARENTPATH) {
    message( 'QXLSX_PARENTPATH is empty. use default value.' )
    QXLSX_PARENTPATH = $$PWD/../
} else {
    message( 'QXLSX_PARENTPATH is not empty.' )
    message( $${QXLSX_PARENTPATH} )
}

isEmpty(QXLSX_HEADERPATH) {
    message( 'QXLSX_HEADERPATH is empty. use default value.' )
    QXLSX_HEADERPATH = $$PWD/../QXlsx/header/
} else {
    message( 'QXLSX_HEADERPATH is not empty.' )
    message( $${QXLSX_HEADERPATH} )
}

isEmpty(QXLSX_SOURCEPATH) {
    message( 'QXLSX_SOURCEPATH is empty. use default value.' )
    QXLSX_SOURCEPATH = $$PWD/../QXlsx/source/
} else {
    message( 'QXLSX_SOURCEPATH is not empty.' )
    message( $${QXLSX_SOURCEPATH} )
}

INCLUDEPATH += $$PWD
INCLUDEPATH += $${QXLSX_PARENTPATH}
INCLUDEPATH += $${QXLSX_HEADERPATH}

########################################
# source code 

HEADERS += $$files($${QXLSX_HEADERPATH}*.h)
SOURCES += $$files($${QXLSX_SOURCEPATH}*.cpp)

########################################
# custom setting for compiler & system

win32-g++ {
    message("compiling for windows g++. mingw or msys or cygwin.")
    INCLUDEPATH += $${QXLSX_HEADERPATH}win32-gcc 
	CONFIG(debug, debug|release) {
	} else {
	}	
}
win32-msvc2013 {
    message("Compiling for Visual Studio 2013")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2013 
	CONFIG(debug, debug|release) {
	} else {
	}		
}
win32-msvc2015 {
    message("Compiling for Visual Studio 2015")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2015 
	CONFIG(debug, debug|release) {
	} else {
	}		
}
win32-msvc2017 {
    message("Compiling for Visual Studio 2017")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2017 
	CONFIG(debug, debug|release) {
	} else {
	}		
}
win32-msvc2019 {
    message("Compiling for Visual Studio 2019")
    INCLUDEPATH += $${QXLSX_HEADERPATH}msvc2019
        CONFIG(debug, debug|release) {
        } else {
        }
}
unix {
   !contains(QT_ARCH, x86_64){
       LIB=lib32
       message("compiling for 32bit linux/unix system")
    } else {
       LIB=lib64
       message("compiling for 64bit linux/unix system")
   }

   INCLUDEPATH += $${QXLSX_HEADERPATH}unix-gcc

    # target.path = /usr/lib
    # INSTALLS += target
	
	CONFIG(debug, debug|release) {
	} else {
	}		
}
mac {
    message("compiling for mac os")
    INCLUDEPATH += $${QXLSX_HEADERPATH}mac
	CONFIG(debug, debug|release) {
	} else {
	}		
}

