#include <chrono>
#include <iostream>

#define Rows 32
#define Cols 10500
#define mean_len 8
#define Cols_avg Cols - mean_len + 1

float A[Rows][Cols];
float averages[Rows][Cols_avg];

int main() {
    for(int i = 0; i < Rows; ++i) {
        for(int j = 0; j < Cols; ++j) {
            A[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        }
    }

    auto start = std::chrono::steady_clock::now();

    for(int i = 0; i < Rows; ++i) {
        float sum{0};

        for(int j = 0; j < mean_len; ++j) {
            sum += A[i][j];
        }

        for(int j = mean_len; j < Cols_avg; ++j) {
            averages[i][j-mean_len] = sum / mean_len;
            sum -= A[i][j-mean_len];
            sum += A[i][j];
        }

    } 

    auto finish = std::chrono::steady_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "Runtime: " << elapsed_time << " ms\n";

    return 0;
}