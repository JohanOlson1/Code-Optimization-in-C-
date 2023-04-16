
#include <omp.h>
#include <stdlib.h>
#include <sys/time.h>

#include <iostream>

#define n 1024
double A[n][n];
double B[n][n];
double C[n][n];

float tdiff(struct timeval* start, struct timeval* end) {
    return (end->tv_sec - start->tv_sec) + 1e-6 * (end->tv_usec - start->tv_usec);
}

int main(int argc, const char* argv[]) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            A[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            B[i][j] = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
            C[i][j] = 0;
        }
    }

    omp_set_num_threads(8);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    #pragma omp parallel for
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < n; ++k) {
            for(int j = 0; j < n; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    gettimeofday(&end, NULL);

    std::cout << tdiff(&start, &end) << " s\n";

    return 0;
}