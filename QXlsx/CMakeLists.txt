# Author: Kang Lin(kl222@126.com)

cmake_minimum_required(VERSION 3.9)

# Qt components
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
SET(QT_COMPONENTS Core Gui)
find_package(Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})
message("QT_VERSION:${Qt5_VERSION}")
FOREACH(_COMPONENT ${QT_COMPONENTS})
    LIST(APPEND QT_LIBRARIES Qt5::${_COMPONENT})
ENDFOREACH()
find_package(Qt5Gui CONFIG REQUIRED Private)
LIST(APPEND QT_LIBRARIES Qt5::GuiPrivate)

get_filename_component(QT_INSTALL_DIR "${Qt5_DIR}/../../.." ABSOLUTE)

# Open qt compile tools
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

project(QXlsx LANGUAGES CXX)

#SET(QXLSX_DEFINEDS 
#    QT_NO_KEYWORDS
#    QT_NO_CAST_TO_ASCII
#    QT_NO_CAST_FROM_ASCII
#    QT_STRICT_ITERATORS
#    QT_NO_URL_CAST_FROM_STRING
#    QT_NO_CAST_FROM_BYTEARRAY
#    QT_USE_QSTRINGBUILDER
#    QT_NO_SIGNALS_SLOTS_KEYWORDS
#    QT_USE_FAST_OPERATOR_PLUS
#    QT_DISABLE_DEPRECATED_BEFORE=0x050c00
#    )

#------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------
# Define target sources
file(GLOB_RECURSE files source/*.cpp)
file(GLOB_RECURSE INSTALLHEADER_FILES 
    header/xlsxabstractooxmlfile.h
    header/xlsxdocument.h
    header/xlsxabstractsheet.h
    header/xlsxcellformula.h
    header/xlsxformat.h
    header/xlsxcell.h
    header/xlsxglobal.h
    header/xlsxcelllocation.h
    header/xlsxcellrange.h
    header/xlsxcellreference.h
    header/xlsxrichstring.h
    header/xlsxchart.h
    header/xlsxchartsheet.h
    header/xlsxconditionalformatting.h
    header/xlsxworkbook.h
    header/xlsxdatavalidation.h
    header/xlsxworksheet.h
    header/xlsxdatetype.h                
    )

SET(QXLSX_LIBS ${QT_LIBRARIES})
#------------------------------------------------------------------------------
# Library
#------------------------------------------------------------------------------
add_library(${PROJECT_NAME} ${files} ${INSTALLHEADER_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    PUBLIC_HEADER "${INSTALLHEADER_FILES}" # Install head files
    VERSION ${BUILD_VERSION}
    )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
target_compile_definitions(${PROJECT_NAME} PUBLIC ${QXLSX_DEFINEDS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${QXLSX_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/header>
    #$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
    )
IF(MSVC)
    # This option is to enable the /MP switch for Visual Studio 2005 and above compilers
    OPTION(ENABLE_MSVC_USE_MP "Set to ON to build with the /MP option (Visual Studio 2005 and above)." ON)
    IF(ENABLE_MSVC_USE_MP)
        target_compile_options(${PROJECT_NAME} PRIVATE /MP)
        target_compile_options(${PROJECT_NAME} PUBLIC
            "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    ENDIF(ENABLE_MSVC_USE_MP)
ENDIF(MSVC)

if(WIN32)
    INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Config
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        )
else()
    INSTALL(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Config
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        )
endif()

export(TARGETS ${PROJECT_NAME}
    APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    )

# Install cmake configure files
install(EXPORT ${PROJECT_NAME}Config
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
    )
# Install cmake version configure file
if(DEFINED PARA_VERSION)
    write_basic_package_version_file(
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PARA_VERSION}
        COMPATIBILITY AnyNewerVersion)
    install(FILES "${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake")
endif()

# Install pkg-config configure file
foreach(v ${QXLSX_DEFINEDS})
    set(PC_QXLSX_DEFINEDS "${PC_QXLSX_DEFINEDS} -D${v}")
endforeach()
configure_file(
  ${CMAKE_SOURCE_DIR}/cmake/QXlsx.pc.in
  "${CMAKE_BINARY_DIR}/QXlsx.pc" @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/QXlsx.pc
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
