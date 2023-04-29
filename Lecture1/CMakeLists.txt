add_executable(lecture1 src/matrix_mul.cc)

target_include_directories(lecture1 PUBLIC include)

target_link_libraries(lecture1      PRIVATE
                                    OpenMP::OpenMP_CXX
                                    IPP::ippcore IPP::ipps IPP::ippi IPP::ippcv
                                    MKL::MKL)