cmake_minimum_required(VERSION 3.16)

project(QXlsx VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt5 5.6.0 REQUIRED COMPONENTS Core Gui)
find_package(Qt5Gui CONFIG REQUIRED Private)
set(CMAKE_AUTOMOC ON)

add_definitions(
    -DQT_NO_KEYWORDS
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
    -DQT_STRICT_ITERATORS
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
    -DQT_USE_FAST_OPERATOR_PLUS
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050c00
)

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
