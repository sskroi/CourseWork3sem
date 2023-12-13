cmake_minimum_required(VERSION 3.28.0)

project(CourseWork3sem VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(CourseWork3sem
    src/main.cpp
    src/menu.cpp
    src/RouteList.cpp
    src/Route.cpp
)

if(UNIX AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(CourseWork3sem PUBLIC -fsanitize=address)
    target_link_options(CourseWork3sem PUBLIC -fsanitize=address)
endif()

target_include_directories(CourseWork3sem PRIVATE ${CMAKE_SOURCE_DIR}/include)