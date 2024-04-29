# CMakeLists.txt for Console Application

# TODO: Set minimum cmake version 
cmake_minimum_required(VERSION 3.14)

# TODO: Set project name 
project(WhatType LANGUAGES CXX)

# TODO: Set Your C++ version
set(CMAKE_CXX_STANDARD 11) # C++ 11

##########################
# bolier-plate code (1) {{

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui REQUIRED)

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

include_directories(${QXLSX_HEADERPATH})

file(GLOB QXLSX_CPP "${QXLSX_SOURCEPATH}/*.cpp")
file(GLOB QXLSX_H "${QXLSX_HEADERPATH}/*.h")

set(SRC_FILES ${QXLSX_CPP})
list(APPEND SRC_FILES ${QXLSX_H})
 
# bolier-plate code (1) }}
###########################

#########################
# Console Application {{

# TODO: set your source code 
set(APP_SRC_FILES
  main.cpp ) 
  
list(APPEND SRC_FILES ${APP_SRC_FILES})
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Console Application }}
########################
 
##########################
# bolier-plate code (2) {{

target_include_directories(${PROJECT_NAME} PRIVATE
 ${QXLSX_HEADERPATH} 
 ${CMAKE_CURRENT_SOURCE_DIR} )
 
target_link_libraries(${PROJECT_NAME} 
 Qt${QT_VERSION_MAJOR}::Core
 Qt${QT_VERSION_MAJOR}::GuiPrivate
 )
 
 set(CMAKE_WIN32_EXECUTABLE OFF)
 
# bolier-plate code (2) }}
##########################

