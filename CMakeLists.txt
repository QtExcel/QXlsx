cmake_minimum_required(VERSION 3.16)

project(QXlsx)

#------------------------------------------------------------------------------
# Qt
#------------------------------------------------------------------------------
find_package(Qt5 REQUIRED QUIET COMPONENTS Core Gui)
find_package(Qt5Gui CONFIG REQUIRED Private)
set(CMAKE_AUTOMOC ON)

#------------------------------------------------------------------------------
# Library
#------------------------------------------------------------------------------
add_library(QXlsx)

#------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------
# Define target sources
file(GLOB_RECURSE files ${CMAKE_SOURCE_DIR}/QXlsx/source/*.cpp ${CMAKE_SOURCE_DIR}/QXlsx/header/*.h)

target_sources(QXlsx PRIVATE
  ${files}
)

target_link_libraries(QXlsx PUBLIC Qt5::Core Qt5::Gui Qt5::GuiPrivate)
target_include_directories(QXlsx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/QXlsx/header)

configure_file(
  ${CMAKE_SOURCE_DIR}/CMake/QXlsxConfig.cmake.in
  "${CMAKE_BINARY_DIR}/QXlsxConfig.cmake" @ONLY)

export(TARGETS QXlsx
  FILE "${CMAKE_BINARY_DIR}/QXlsxTargets.cmake")
