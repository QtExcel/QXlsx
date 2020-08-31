# Author: Kang Lin(kl222@126.com)

cmake_minimum_required(VERSION 3.9)

project(TestExcel LANGUAGES CXX)

SET(SOURCES
    calendar.cpp
    chart.cpp
    chartextended.cpp
    chartsheet.cpp
    datavalidation.cpp
    definename.cpp
    demo.cpp
    documentproperty.cpp
    extractdata.cpp
    formulas.cpp
    hello.cpp
    hyperlinks.cpp
    image.cpp
    main.cpp
    mergecells.cpp
    numberformat.cpp
    richtext.cpp
    rowcolumn.cpp
    style.cpp
    worksheetoperations.cpp
    readStyle.cpp
    pageMargins.cpp)

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
