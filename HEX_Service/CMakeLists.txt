cmake_minimum_required(VERSION 3.5)
project(HEX_Service VERSION 0.1 LANGUAGES CXX)

# --- włącz automatyczne UIC/MOC/RCC i ustaw C++17 ---
set(CMAKE_AUTOUIC    ON)
set(CMAKE_AUTOMOC    ON)
set(CMAKE_AUTORCC    ON)
set(CMAKE_CXX_STANDARD       17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- znajdź Qt5 Widgets oraz Charts ---
find_package(Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt5Charts REQUIRED)


# --- lista wszystkich plików źródłowych i nagłówków ---
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
)

# --- tworzony cel wykonywalny ---
add_executable(HEX_Service
    ${PROJECT_SOURCES}
    fmqualityview.h
    fmqualityview.cpp
)
target_link_libraries(HEX_Service
  PRIVATE
    Qt5::Widgets
    Qt5::Charts
)
target_include_directories(HEX_Service PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# --- dołącz biblioteki Qt ---
target_link_libraries(HEX_Service
    PRIVATE
      Qt5::Widgets
      Qt5::Charts
)

# --- zapewnij, że kompilator znajdzie wszystkie nagłówki ---
target_include_directories(HEX_Service
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}
)

# --- kopiowanie pliku z danymi do katalogu build ---
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/servo_test_data.txt
    ${CMAKE_BINARY_DIR}/servo_test_data.txt
    COPYONLY
)

# --- (opcjonalnie kopiuj też inne pliki z data/) ---
# configure_file(data/servo_test_data_comm.txt
#                ${CMAKE_BINARY_DIR}/servo_test_data_comm.txt
#                COPYONLY)

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
