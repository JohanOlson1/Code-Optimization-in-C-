add_executable(lecture6 src/parallelization.cc)

target_include_directories(lecture6 PUBLIC include)

target_link_libraries(lecture6  PRIVATE 
                                OpenMP::OpenMP_CXX)