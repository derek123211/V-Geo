cmake_minimum_required(VERSION 3.16)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:\\mingw64\\lib\\cmake")

find_package(SFML REQUIRED COMPONENTS audio network graphics window system)

if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML NOT FOUND!")
else()
    message("SFML FOUND!")
endif()

include_directories(${SFML_INCLUDE_DIR})
add_executable(MyProject main.cpp include/vector2.h include/numeric.h include/edge.h include/triangle.h include/delaunay.h include/voronoisquare.h)
target_link_libraries(MyProject sfml-audio sfml-network sfml-graphics sfml-window sfml-system)