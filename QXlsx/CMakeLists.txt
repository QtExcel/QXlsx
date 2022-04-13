# CMakeLists.txt for QXlsx Library

cmake_minimum_required(VERSION 3.14)

project(QXlsx LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

if(NOT DEFINED ${QXLSX_PARENTPATH})
	set(QXLSX_PARENTPATH ${CMAKE_CURRENT_SOURCE_DIR}/../)
endif(NOT DEFINED ${QXLSX_PARENTPATH}) 
	
if(NOT DEFINED ${QXLSX_HEADERPATH})	
	set(QXLSX_HEADERPATH ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx/header/)
endif(NOT DEFINED ${QXLSX_HEADERPATH})		

if(NOT DEFINED ${QXLSX_SOURCEPATH})
	set(QXLSX_SOURCEPATH ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx/source/)
endif(NOT DEFINED ${QXLSX_SOURCEPATH})	

message("Current Path of QXlsx")
message(${QXLSX_PARENTPATH})
message(${QXLSX_HEADERPATH})
message(${QXLSX_SOURCEPATH})

file(GLOB QXLSX_CPP "${QXLSX_SOURCEPATH}/*.cpp")
file(GLOB QXLSX_H "${QXLSX_HEADERPATH}/*.h")

set(SRC_FILES ${QXLSX_CPP})
list(APPEND SRC_FILES ${QXLSX_H})

add_library(QXlsx STATIC
 ${SRC_FILES} )

target_include_directories(QXlsx PRIVATE ${QXLSX_HEADERPATH})

target_link_libraries(${PROJECT_NAME}
 Qt${QT_VERSION_MAJOR}::Core
 Qt${QT_VERSION_MAJOR}::GuiPrivate
 )

target_compile_definitions(QXlsx PRIVATE QXLSX_LIBRARY)

# install the library on a system
include(GNUInstallDirs)
install(FILES ${QXLSX_H} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/qxlsx)
install(
    TARGETS QXlsx
    EXPORT QXlsxTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
    EXPORT QXlsxTargets
    FILE QXlsxTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QXlsx
    NAMESPACE QXlsx::
)
include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake/QXlsxConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/QXlsxConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QXlsx
)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/QXlsxConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QXlsx
)
