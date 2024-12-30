# CMakeLists.txt for QXlsx Library

cmake_minimum_required(VERSION 3.16)

project(QXlsx
    VERSION 1.5.0
    LANGUAGES CXX
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)

if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
endif()
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)
set(EXPORT_NAME QXlsxQt${QT_VERSION_MAJOR})

if (QT_VERSION_MAJOR EQUAL 6)
    set(CMAKE_CXX_STANDARD 17 CACHE STRING "")
else()
    set(CMAKE_CXX_STANDARD 11 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

if(NOT DEFINED QXLSX_PARENTPATH)
    set(QXLSX_PARENTPATH ${CMAKE_CURRENT_SOURCE_DIR}/../)
endif()

if(NOT DEFINED QXLSX_HEADERPATH)
    set(QXLSX_HEADERPATH ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx/header/)
endif()

if(NOT DEFINED QXLSX_SOURCEPATH)
    set(QXLSX_SOURCEPATH ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx/source/)
endif()

# Due historical reasons this value is kept off
option(BUILD_SHARED_LIBS "Build in shared lib mode" OFF)

set(SRC_FILES
    source/xlsxcellrange.cpp
    source/xlsxcellrange.cpp
    source/xlsxcontenttypes.cpp
    source/xlsxdrawinganchor.cpp
    source/xlsxrichstring.cpp
    source/xlsxworkbook.cpp
    source/xlsxabstractooxmlfile.cpp
    source/xlsxcellreference.cpp
    source/xlsxdatavalidation.cpp
    source/xlsxdrawing.cpp
    source/xlsxsharedstrings.cpp
    source/xlsxworksheet.cpp
    source/xlsxabstractsheet.cpp
    source/xlsxchart.cpp
    source/xlsxdatetype.cpp
    source/xlsxformat.cpp
    source/xlsxsimpleooxmlfile.cpp
    source/xlsxzipreader.cpp
    source/xlsxcell.cpp
    source/xlsxchartsheet.cpp
    source/xlsxdocpropsapp.cpp
    source/xlsxmediafile.cpp
    source/xlsxstyles.cpp
    source/xlsxzipwriter.cpp
    source/xlsxcellformula.cpp
    source/xlsxcolor.cpp
    source/xlsxdocpropscore.cpp
    source/xlsxnumformatparser.cpp
    source/xlsxtheme.cpp
    source/xlsxcelllocation.cpp
    source/xlsxconditionalformatting.cpp
    source/xlsxdocument.cpp
    source/xlsxrelationships.cpp
    source/xlsxutility.cpp
    header/xlsxabstractooxmlfile_p.h
    header/xlsxchartsheet_p.h
    header/xlsxdocpropsapp_p.h
    header/xlsxformat_p.h
    header/xlsxsharedstrings_p.h
    header/xlsxworkbook_p.h
    header/xlsxabstractsheet_p.h
    header/xlsxcolor_p.h
    header/xlsxdocpropscore_p.h
    header/xlsxmediafile_p.h
    header/xlsxsimpleooxmlfile_p.h
    header/xlsxworksheet_p.h
    header/xlsxcellformula_p.h
    header/xlsxconditionalformatting_p.h
    header/xlsxdocument_p.h
    header/xlsxnumformatparser_p.h
    header/xlsxstyles_p.h
    header/xlsxzipreader_p.h
    header/xlsxcell_p.h
    header/xlsxcontenttypes_p.h
    header/xlsxdrawinganchor_p.h
    header/xlsxrelationships_p.h
    header/xlsxtheme_p.h
    header/xlsxzipwriter_p.h
    header/xlsxchart_p.h
    header/xlsxdatavalidation_p.h
    header/xlsxdrawing_p.h
    header/xlsxrichstring_p.h
    header/xlsxutility_p.h
)

set(QXLSX_PUBLIC_HEADERS
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

add_library(QXlsx::QXlsx ALIAS QXlsx)

target_compile_definitions(QXlsx PRIVATE
    QT_NO_KEYWORDS
    QT_NO_CAST_TO_ASCII
    QT_NO_CAST_FROM_ASCII
    QT_NO_URL_CAST_FROM_STRING
    QT_NO_CAST_FROM_BYTEARRAY
    QT_USE_QSTRINGBUILDER
    QT_NO_SIGNALS_SLOTS_KEYWORDS
    QT_USE_FAST_OPERATOR_PLUS
    QT_DISABLE_DEPRECATED_BEFORE=0x060600
)

if (NOT WIN32)
    # Strict iterators can't be used on Windows, they lead to a link error
    # when application code iterates over a QVector<QPoint> for instance, unless
    # Qt itself was also built with strict iterators.
    # See example at https://bugreports.qt.io/browse/AUTOSUITE-946
    target_compile_definitions(QXlsx PRIVATE QT_STRICT_ITERATORS)
endif()

target_compile_features(QXlsx INTERFACE cxx_std_11)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(QXlsx PUBLIC QXlsx_SHAREDLIB)
endif()

target_link_libraries(${PROJECT_NAME}
   Qt${QT_VERSION_MAJOR}::Core
   Qt${QT_VERSION_MAJOR}::GuiPrivate
)

target_include_directories(QXlsx
PRIVATE
    ${QXLSX_HEADERPATH}
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/header>
    $<INSTALL_INTERFACE:include/QXlsxQt${QT_VERSION_MAJOR}>
)

set_target_properties(QXlsx PROPERTIES
    OUTPUT_NAME ${EXPORT_NAME}
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${QXLSX_PUBLIC_HEADERS}"
)

install(TARGETS QXlsx
    EXPORT ${EXPORT_NAME}Targets DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT runtime
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT devel
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QXlsxQt${QT_VERSION_MAJOR} COMPONENT devel
)

install(EXPORT ${EXPORT_NAME}Targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}/
    FILE ${EXPORT_NAME}Targets.cmake
    NAMESPACE QXlsx::
    COMPONENT devel
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/qxlsx-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${EXPORT_NAME}Config.cmake
    @ONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/qxlsx-config-version.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${EXPORT_NAME}ConfigVersion.cmake
    @ONLY
)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${EXPORT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${EXPORT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}/
)
include(CPackConfig)
