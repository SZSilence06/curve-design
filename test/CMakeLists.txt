cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(framework-test)

include(../default.cmake)

add_subdirectory(../src/alg ${CMAKE_CURRENT_BINARY_DIR}/alg)
add_subdirectory(../src/globals ${CMAKE_CURRENT_BINARY_DIR}/globals)

file(GLOB header *.h)
file(GLOB source *.cpp)

add_executable(framework-test ${header} ${source})

target_link_libraries(framework-test
    jtf-mesh
    alg)

