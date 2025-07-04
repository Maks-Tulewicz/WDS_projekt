cmake_minimum_required(VERSION 3.5)
project(HEX_Service VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC    ON)
set(CMAKE_AUTOMOC    ON)
set(CMAKE_AUTORCC    ON)
set(CMAKE_CXX_STANDARD       17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Charts Core SerialPort)
find_package(Qt5Charts REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    servoanglemanager.cpp
    servoanglemanager.h
    datareader.cpp
    datareader.h
    datasimulator.cpp
    datasimulator.h
    sideview.cpp
    sideview.h
    topview.cpp
    topview.h
    icons.qrc
    translations.qrc
    fmqualityview.h
    fmqualityview.cpp
)

add_executable(HEX_Service
    ${PROJECT_SOURCES}
)

target_include_directories(HEX_Service PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HEX_Service
  PRIVATE
    Qt5::Widgets
    Qt5::Charts
    Qt5::Core
    Qt5::SerialPort
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/servo_test_data.txt
    ${CMAKE_BINARY_DIR}/servo_test_data.txt
    COPYONLY
)

# --- wsparcie Doxygen — nie trzeba modyfikować ---
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
