# CMakeLists.txt for QXlsx Library

cmake_minimum_required(VERSION 3.16)

project(QXlsx
    VERSION 1.4.4
    LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

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

# Due historical reasons this value is kept off
option(BUILD_SHARED_LIBS "Build in shared lib mode" OFF)

file(GLOB QXLSX_CPP "${QXLSX_SOURCEPATH}/*.cpp")
file(GLOB QXLSX_H "${QXLSX_HEADERPATH}/*.h")

set(SRC_FILES ${QXLSX_CPP})
list(APPEND SRC_FILES ${QXLSX_H})

set(QXLSX_PUBLIC_HEADERS
    header/xlsxdocument.h
    header/xlsxabstractooxmlfile.h
    header/xlsxabstractsheet.h
    header/xlsxabstractsheet_p.h
    header/xlsxcellformula.h
    header/xlsxcell.h
    header/xlsxcelllocation.h
    header/xlsxcellrange.h
    header/xlsxcellreference.h
    header/xlsxchart.h
    header/xlsxchartsheet.h
    header/xlsxconditionalformatting.h
    header/xlsxdatavalidation.h
    header/xlsxdatetype.h
    header/xlsxdocument.h
    header/xlsxformat.h
    header/xlsxglobal.h
    header/xlsxrichstring.h
    header/xlsxworkbook.h
    header/xlsxworksheet.h
)

add_library(QXlsx
    ${SRC_FILES}
    ${QXLSX_PUBLIC_HEADERS}
)
add_library(QXlsx::Core ALIAS QXlsx)

target_include_directories(QXlsx PRIVATE ${QXLSX_HEADERPATH})

target_link_libraries(${PROJECT_NAME}
 Qt${QT_VERSION_MAJOR}::Core
 Qt${QT_VERSION_MAJOR}::GuiPrivate
 )

set_property(TARGET QXlsx PROPERTY PUBLIC_HEADER ${QXLSX_PUBLIC_HEADERS})

target_include_directories(QXlsx PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/header>
  $<INSTALL_INTERFACE:include/QXlsx>
)

set_target_properties(QXlsx PROPERTIES
    EXPORT_NAME Core
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
)

install(TARGETS QXlsx
    EXPORT QXlsxTargets DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION bin COMPONENT runtime
    ARCHIVE DESTINATION lib COMPONENT devel
    PUBLIC_HEADER DESTINATION include/QXlsx COMPONENT devel
)

install(EXPORT QXlsxTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QXlsx/
    FILE QXlsxTargets.cmake
    NAMESPACE QXlsx::
    COMPONENT Devel
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/qxlsx-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/QXlsxConfig.cmake
    @ONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/qxlsx-config-version.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/QXlsxConfigVersion.cmake
    @ONLY
)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QXlsxConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/QXlsxConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QXlsx/
)

target_compile_definitions(QXlsx PRIVATE QXLSX_LIBRARY)

include(CPackConfig)
