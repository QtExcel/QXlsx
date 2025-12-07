cmake_minimum_required(VERSION 3.26)
project(ExcelViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Tell QXlsx which Qt major version to use.
set(QT_VERSION_MAJOR 6)

# Add QXlsx from one directory above the current project.
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx
    ${CMAKE_CURRENT_BINARY_DIR}/QXlsx_build
)

add_executable(ExcelViewer
    main.cpp
    mainwindow.h
    mainwindow.cpp
    excelmodel.h
    excelmodel.cpp
)

target_link_libraries(ExcelViewer PRIVATE
    Qt6::Widgets
    QXlsx::QXlsx
)

# Get full git hash of QXlsx (40 characters)
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
    OUTPUT_VARIABLE QXLSX_GIT_FULL_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "QXlsx Git full hash = ${QXLSX_GIT_FULL_HASH}")

# Pass it to C++ code as a define
add_compile_definitions(QXLSX_GIT_FULL_HASH="${QXLSX_GIT_FULL_HASH}")


