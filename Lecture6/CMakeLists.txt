add_executable(Lecture6 main.cc)

find_package(OpenMP)
target_link_libraries(Lecture6  PRIVATE 
                                OpenMP::OpenMP_CXX)