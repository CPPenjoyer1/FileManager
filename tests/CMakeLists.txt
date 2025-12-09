cmake_minimum_required(VERSION 3.16)

project(FileManagerTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test)

add_executable(${PROJECT_NAME}
    main.cpp
    test.cpp
    test.hpp
)

target_link_libraries(${PROJECT_NAME}
    FileManagerLib
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Test
)

