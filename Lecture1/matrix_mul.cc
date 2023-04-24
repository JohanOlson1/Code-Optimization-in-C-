#include "matrix_mul.h"

#include <omp.h>

#include <chrono>
#include <iostream>

#include "ipps.h"
#include "mkl.h"

#define n 4096
double A[n][n];
double B[n][n];
double C[n][n];

int main() {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            A[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            B[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            C[i][j] = 0;
        }
    }

    auto start = std::chrono::steady_clock::now();
    // naiveApproach();
    // loopOrder();
    // optimizationFlag();
    // parallelization();
    tiling();
    // vectorization();
    // intelMKL(); // Intel MKL
    auto finish = std::chrono::steady_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "Runtime: " << elapsed_time << " ms\n";

    return 0;
}

#pragma GCC optimize("O0")
void naiveApproach() {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

#pragma GCC optimize("O0")
void loopOrder() {
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < n; ++k) {
            for(int j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

#pragma GCC optimize("O3")
void optimizationFlag() {
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < n; ++k) {
            for(int j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

#pragma GCC optimize("O3")
void parallelization() {

    #pragma omp parallel for schedule(dynamic) num_threads(omp_get_max_threads())
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < n; ++k) {
            for(int j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

#pragma GCC optimize("O3")
void tiling() {
    int s{64};

    omp_set_num_threads(omp_get_max_threads());

    #pragma omp parallel for
    for(int ih = 0; ih < n; ih += s) {
        #pragma omp parallel for
        for(int jh = 0; jh < n; jh += s) {
            for(int kh = 0; kh < n; kh += s) {
                for(int il = 0; il < s; ++il) {
                    for(int kl = 0; kl < s; ++kl) {
                        for(int jl = 0; jl < s; ++jl) {
                            C[ih+il][jh+jl] += A[ih+il][kh+kl] * B[kh+kl][jh+jl];
                        }
                    }
                }
            }
        }
    }
}

// O3 flag does vectorization well, adds all the neccessary flags
#pragma GCC optimize("O3")
void vectorization() {
    
    int s{64};

    omp_set_num_threads(omp_get_max_threads());

    #pragma omp parallel for
    for(int ih = 0; ih < n; ih += s) {
        #pragma omp parallel for
        for(int jh = 0; jh < n; jh += s) {
            for(int kh = 0; kh < n; kh += s) {
                for(int il = 0; il < s; ++il) {
                    for(int kl = 0; kl < s; ++kl) {
                        for(int jl = 0; jl < s; ++jl) {
                            C[ih+il][jh+jl] += A[ih+il][kh+kl] * B[kh+kl][jh+jl];
                        }
                    }
                }
            }
        }
    }
}

void intelMKL() {
    mkl_set_num_threads(1);
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1, &A[0][0], n, &B[0][0], n, 0, &C[0][0], n);
}