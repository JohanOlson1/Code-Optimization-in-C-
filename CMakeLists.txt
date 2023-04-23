cmake_minimum_required(VERSION 3.0.0)
project(CodeOptimization VERSION 0.1.0)

find_package(OpenMP)

set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -march=native")

add_executable(Executable lecture_1_matrix_mul.cc)

find_package(IPP)
find_package(MKL)
target_link_libraries(Executable    PRIVATE 
                                    OpenMP::OpenMP_CXX
                                    IPP::ippcore IPP::ipps IPP::ippi IPP::ippcv
                                    MKL::MKL)
                                                                        