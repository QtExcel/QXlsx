cmake_minimum_required(VERSION 3.16)

project(QXlsx VERSION 1.3.56 LANGUAGES CXX)

include(GNUInstallDirs)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Gui)
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
set_target_properties(QXlsx PROPERTIES
	SOVERSION ${PROJECT_VERSION})

#------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------
# Define target sources
file(GLOB_RECURSE files_cpp ${PROJECT_SOURCE_DIR}/QXlsx/source/*.cpp)
file(GLOB_RECURSE files_h ${PROJECT_SOURCE_DIR}/QXlsx/header/*.h)

target_sources(QXlsx PRIVATE
  ${files_cpp} ${files_h}
)

target_link_libraries(QXlsx PUBLIC Qt5::Gui Qt5::GuiPrivate)
target_include_directories(QXlsx
	PRIVATE ${PROJECT_SOURCE_DIR}/QXlsx/header
	INTERFACE ${CMAKE_INSTALL_FULL_INCLUDEDIR}/QXlsx)

configure_file(
  ${PROJECT_SOURCE_DIR}/CMake/QXlsxConfig.cmake.in
  "${PROJECT_BINARY_DIR}/QXlsxConfig.cmake" @ONLY)

export(TARGETS QXlsx
  FILE "${PROJECT_BINARY_DIR}/QXlsxTargets.cmake")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(${PROJECT_BINARY_DIR}/QXlsxConfigVersion.cmake
	COMPATIBILITY AnyNewerVersion)
install(TARGETS QXlsx EXPORT QXlsxTargets)
install(FILES
	${PROJECT_BINARY_DIR}/QXlsxConfig.cmake
	${PROJECT_BINARY_DIR}/QXlsxConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_DATADIR}/QXlsx/cmake)
install(EXPORT QXlsxTargets DESTINATION ${CMAKE_INSTALL_DATADIR}/QXlsx/cmake)
install(FILES ${files_h} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QXlsx)
