cmake_minimum_required(VERSION 3.25.2)

project(project VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "F:\\Qt5\\5.15.2\\mingw81_64")
find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(project
    network.cpp
    mainwindow.cpp
    mainwindow.h
    main.cpp
    json.hpp
)

target_link_libraries(project PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui)

set_target_properties(project PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
