cmake_minimum_required(VERSION 3.26)

project(ExcelTableEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

# QXlsx library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx QXlsx_build)

# Qt 6 
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(ExcelTableEditor
    main.cpp
    mainwindow.h
    mainwindow.cpp
    excelitemdelegate.h
    excelitemdelegate.cpp
)

target_link_libraries(ExcelTableEditor
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        QXlsx::QXlsx
)

set(CMAKE_WIN32_EXECUTABLE ON)
