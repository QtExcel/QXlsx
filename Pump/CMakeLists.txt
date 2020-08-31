# Author: Kang Lin(kl222@126.com)

cmake_minimum_required(VERSION 3.9)

project(Pump LANGUAGES CXX)

SET(SOURCES
    main.cpp
    test.cpp)
SET(RESOURCES pump.qrc)
#------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VERSION ${BUILD_VERSION}
    )
target_link_libraries(${PROJECT_NAME} PRIVATE QXlsx)

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )
