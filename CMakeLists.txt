cmake_minimum_required(VERSION 3.28.0)

project(CourseWork3sem VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(CourseWork3sem
    src/main.cpp
    src/menu.cpp
    src/RouteList.cpp
)