################################################################################
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
################################################################################
# UseQXlsx.pri

QT += core

# link QXlsx library 
LIBS += -lQXlsx 

################################################################################
# set include & libs path for your own test environment

win32-g++ {

        INCLUDEPATH += "../QXlsx/header"

	contains(QMAKE_HOST.arch, x86_64):{	
                message("Host is 64bit. (maybe msys2)") # we will gonna use msys2/x64
		CONFIG(debug, debug|release) {		
			message("Host is debug mode")
			LIBS += -L"../QXlsx/debug"
		} else {
			message("Host is release mode")
			LIBS += -L"../QXlsx/release"
		}
	} else {
                message("Host is mingw. (or msys1 or cygwin)") # it can be msys or cygwin 32bit
		CONFIG(debug, debug|release) {
			message("Host is debug mode")
			contains(QT_VERSION, 5.6.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.6.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_1_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.6.2) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_2_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.7.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.7.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.8.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_8_0_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.9.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_0_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.9.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_1_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.9.2) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_2_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.10.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_10_0_MinGW_32bit-Debug/debug"
			}
			contains(QT_VERSION, 5.10.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_10_1_MinGW_32bit-Debug/debug"
			}		
		} else {
			message("Host is release mode")
			contains(QT_VERSION, 5.6.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.6.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.6.2) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_6_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.7.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.7.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_7_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.8.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_8_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.9.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.9.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_1_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.9.2) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_9_2_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.10.0) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_10_0_MinGW_32bit-Release/release"
			}
			contains(QT_VERSION, 5.10.1) {
				LIBS += -L"../build-QXlsx-Desktop_Qt_5_10_1_MinGW_32bit-Release/release"
			}		
		}
	}

}
linux-g++ {
    INCLUDEPATH += "../QXlsx/header"
    LIBS += -L"../QXlsx/"
}
win32-msvc2012 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug"
    } else {
        LIBS += -L"../QXlsx/release"
    }
}
win32-msvc2013 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug"
    } else {
        LIBS += -L"../QXlsx/release"
    }
}
win32-msvc2015 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug"
    } else {
        LIBS += -L"../QXlsx/release"
    }
}
win32-msvc2017 {
    CONFIG(debug, debug|release) {
        LIBS += -L"../QXlsx/debug"
    } else {
        LIBS += -L"../QXlsx/release"
    }
} 
mac {
    CONFIG(debug, debug|release) {
    } else {
    }
}
