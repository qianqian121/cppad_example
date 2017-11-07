cmake_minimum_required(VERSION 2.8)
project(cppad)

add_executable(poly_test poly_test.cpp)

target_link_libraries(poly_test
        ipopt)