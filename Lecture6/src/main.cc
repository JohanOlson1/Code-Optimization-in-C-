#include "main.h"

#include <omp.h>
#include <pthread.h>

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main() {
    const int n{40};

    auto start = std::chrono::steady_clock::now();
    // fib(n);
    // pthreadParallelFib(n);
    // cppParallel(n);
    openMPParallel(n);
    auto finish = std::chrono::steady_clock::now();
    double elapsed_time = std::chrono::duration<double, std::milli>(finish - start).count();
    std::cout << "Runtime: " << elapsed_time << " ms\n";
    return 0;
}

static int openMPFib(const int n) {
    int x, y;
    if(n < 2) {
        return n;
    } else {

    #pragma omp task shared(x)
        x = fib(n - 1);
    #pragma omp task shared(y)
        y = fib(n - 2);

    #pragma omp taskwait
        return x + y;
    }
}

void openMPParallel(const int n) {
    int result{0};

    #pragma omp parallel
    {
        #pragma omp single
        result = openMPFib(n);
    }

    std::cout << "fib of " << n << " is: " << result << "\n";    
}

void cppParallel(const int n) {
    auto future{std::async(fib, n - 1)};
    int thrd_1_res{fib(n - 2)};
    int thrd_2_res{future.get()};

    std::cout << "fib of " << n << " is: " << thrd_1_res + thrd_2_res << "\n";
}

void pthreadParallelFib(const int n) {
    pthread_t thread;
    thread_args args;
    int result1{0};

    args.input = n - 1;
    pthread_create(&thread, NULL, threadFunc, static_cast<void*>(&args));
    result1 = fib(n - 2);
    pthread_join(thread, NULL);

    result1 += args.output;

    std::cout << "fib of " << n << " is: " << result1 << "\n";
}

int fib(int n) {
    if (n < 2) {
        return n;
    } else {
        int x{fib(n - 1)};
        int y{fib(n - 2)};
        return x + y;
    }
}

void* threadFunc(void* ptr) {
    int i{static_cast<thread_args*>(ptr)->input};
    static_cast<thread_args*>(ptr)->output = fib(i);
    return NULL;
}

