# Author: Kang Lin(kl222@126.com)

cmake_minimum_required(VERSION 3.9)

if(POLICY CMP0083)
    cmake_policy(SET CMP0083 NEW)
endif()

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()

# Create the file that will be delete
CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
# Create the target that will be delete
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

include(GNUInstallDirs)
include(GenerateExportHeader)

#TODO: Modify version
SET(BUILD_VERSION "v1.3.56")
# Find Git Version Patch
IF(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    if(NOT GIT)
        SET(GIT $ENV{GIT})
    endif()
    if(NOT GIT)
        FIND_PROGRAM(GIT NAMES git git.exe git.cmd)
    endif()
    IF(GIT)
        EXECUTE_PROCESS(
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMAND ${GIT} describe --tags
            OUTPUT_VARIABLE GIT_VERSION  OUTPUT_STRIP_TRAILING_WHITESPACE
        )
	    if(NOT GIT_VERSION)
            EXECUTE_PROCESS(
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                COMMAND ${GIT} rev-parse --short HEAD
                OUTPUT_VARIABLE GIT_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE
            )
        endif()
        SET(BUILD_VERSION ${GIT_VERSION})
    ENDIF()
ENDIF()
message("BUILD_VERSION:${BUILD_VERSION}")

project(QXlsx LANGUAGES CXX)

add_subdirectory(QXlsx)

option(ENABLE_EXAMPLE "Enable example" ON)
if(ENABLE_EXAMPLE)
    add_subdirectory(HelloWorld)
    add_subdirectory(ReadColor)
    add_subdirectory(ShowConsole)
    add_subdirectory(WhatType)
    add_subdirectory(WebServer)
    add_subdirectory(Pump)
    add_subdirectory(DateTime)
    add_subdirectory(IssueTest)
    add_subdirectory(TestExcel)
    add_subdirectory(chartsquestions)
endif()
