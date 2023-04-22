#include "lecture_1_matrix_mul.h"

#include <omp.h>

#include <chrono>
#include <iostream>


int main() {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            A[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            B[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            C[i][j] = 0;
        }
    }

    // 1. Start
    auto start = std::chrono::steady_clock::now();
    naiveApproach();
    auto finish = std::chrono::steady_clock::now();
    double elapsed_time_1 = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "1. Start: " << elapsed_time_1 << " ms\n";

    // 2.  Loop order
    start = std::chrono::steady_clock::now();
    loopOrder();
    finish = std::chrono::steady_clock::now();
    auto elapsed_time_2 = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "2. Loop order: " << elapsed_time_2 << " ms" 
              << " Relative speedup: " << elapsed_time_1/elapsed_time_2 << "\n";

    // 3. Optimization flag
    start = std::chrono::steady_clock::now();
    optimizationFlag();
    finish = std::chrono::steady_clock::now();
    auto elapsed_time_3 = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "3. Optimization flag: " << elapsed_time_3 << " ms" 
              << " Relative speedup: " << elapsed_time_2/elapsed_time_3 << "\n";

    // 4. Parallelization
    start = std::chrono::steady_clock::now();
    parallelization();
    finish = std::chrono::steady_clock::now();
    auto elapsed_time_4 = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "4. Parallel 8 threads: " << elapsed_time_4 << " ms" 
              << " Relative speedup: " << elapsed_time_3/elapsed_time_4 << "\n";

    // 5. Tiling
    start = std::chrono::steady_clock::now();
    tiling();
    finish = std::chrono::steady_clock::now();
    auto elapsed_time_5 = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "5. Tiling: " << elapsed_time_5 << " ms" 
              << " Relative speedup: " << elapsed_time_4/elapsed_time_5 << "\n";
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

    int N_threads{omp_get_max_threads()};

    #pragma omp parallel for num_threads(N_threads)
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
    int s{32};

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