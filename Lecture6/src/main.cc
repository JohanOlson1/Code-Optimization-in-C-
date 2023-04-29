#include "main.h"

#include <omp.h>
#include <pthread.h>

#include <chrono>
#include <iostream>

int main() {
    const int n{40};

    auto start = std::chrono::steady_clock::now();
    // fib(n);
    pthread_parallel_fib(n);
    auto finish = std::chrono::steady_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "Runtime: " << elapsed_time << " ms\n";
    return 0;
}

void pthread_parallel_fib(const int n) {
    pthread_t thread;
    thread_args args;
    int result{0};

    args.input = n - 1;
    pthread_create(&thread, NULL, thread_func, static_cast<void*>(&args));
    result = fib(n - 2);
    pthread_join(thread, NULL);

    result += args.output;

    std::cout << "fib of " << n << " is: " << result << "\n";
}


int fib(int n) {
    if (n < 2) {
        return n;
    } else {
        int x{fib(n-1)};
        int y{fib(n-2)};
        return x + y;
    }
}

void* thread_func(void* ptr) {
    int i{static_cast<thread_args*>(ptr)->input};
    static_cast<thread_args*>(ptr)->output = fib(i);
    return NULL;
}