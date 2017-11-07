cmake_minimum_required(VERSION 2.8)
project(cppad)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(poly_test poly_test.cpp)

target_link_libraries(poly_test
        ipopt)