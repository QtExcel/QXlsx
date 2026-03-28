cmake_minimum_required(VERSION 3.16)

project(LargeData LANGUAGES CXX)

# C++ standard configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt automatic processing
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

#
# 1) Add QXlsx library
#    Your directory structure should be:
#        /QXlsx
#        /LargeData
#
#    So LargeData/CMakeLists.txt runs add_subdirectory("../QXlsx")
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../QXlsx QXlsx_build)

#
# 2) Find Qt6 modules
#    Core is enough for console program.
#
find_package(Qt6 COMPONENTS Core REQUIRED)

#
# 3) Build executable
#
add_executable(LargeData
    main.cpp
)

#
# 4) Link against QXlsx and Qt6::Core
#
target_link_libraries(LargeData
    PRIVATE
        Qt6::Core
        QXlsx::QXlsx
)

# Build as console application
set(CMAKE_WIN32_EXECUTABLE OFF)
