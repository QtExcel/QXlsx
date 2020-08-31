# Author: Kang Lin(kl222@126.com)

cmake_minimum_required(VERSION 3.9)

project(WebServer)

# Qt components
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
SET(QT_COMPONENTS Network)
find_package(Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})
message("QT_VERSION:${Qt5_VERSION}")
FOREACH(_COMPONENT ${QT_COMPONENTS})
    LIST(APPEND QT_LIBRARIES Qt5::${_COMPONENT})
ENDFOREACH()

# Open qt compile tools
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON)

SET(SOURCES
    main.cpp
    context.hpp
    recurse.hpp
    response.hpp
    request.hpp)

SET(RESOURCES ws.qrc)
#------------------------------------------------------------------------------
# Target
#------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${UI_FILES} ${RESOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    VERSION ${BUILD_VERSION}
    )
target_link_libraries(${PROJECT_NAME} PRIVATE QXlsx ${QT_LIBRARIES})
if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:CONSOLE)
endif()

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )
