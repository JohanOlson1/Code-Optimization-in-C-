cmake_minimum_required(VERSION 3.0.0)
project(CodeOptimization VERSION 0.1.0)

find_package(OpenMP)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(Executable lecture_1_matrix_mul.cc)

target_link_libraries(Executable PRIVATE OpenMP::OpenMP_CXX)