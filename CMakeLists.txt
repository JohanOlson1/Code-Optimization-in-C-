cmake_minimum_required(VERSION 3.0.0)
project(CodeOptimization    VERSION 1.0.0
                            DESCRIPTION "Testing code optimizaion"
                            LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILDTYPE "Release")
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -march=native")

find_package(OpenMP)
find_package(IPP)
find_package(MKL)

add_subdirectory(Lecture1)
add_subdirectory(Lecture6)