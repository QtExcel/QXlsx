# CMakeLists.txt for Console Application

# TODO: Set minimum cmake version 
cmake_minimum_required(VERSION 3.14)

# TODO: Set project name 
project(HelloWorld LANGUAGES CXX)

# TODO: Set Your C++ version
set(CMAKE_CXX_STANDARD 11) # C++ 11

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

add_subdirectory(QXlsx)

#########################
# Console Application {{

add_executable(HelloWorld main.cpp)
target_link_libraries(HelloWorld PRIVATE QXlsx::QXlsx)

# Console Application }}
########################
