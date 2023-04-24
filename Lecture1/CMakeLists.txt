add_executable(Executable matrix_mul.cc)

find_package(OpenMP)
find_package(IPP)
find_package(MKL)
target_link_libraries(Executable    PRIVATE 
                                    OpenMP::OpenMP_CXX
                                    IPP::ippcore IPP::ipps IPP::ippi IPP::ippcv
                                    MKL::MKL)