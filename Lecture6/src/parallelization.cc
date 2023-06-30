#include "parallelization.h"

#include <omp.h>
#include <pthread.h>

#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <string>
#include <thread>

using namespace std::chrono;

void Benchmark(std::function<void(int)> f, const int input_argument, const int repeats) {
    const auto start{high_resolution_clock::now()};
    for(int i = 0; i < repeats; ++i) {
        f(input_argument);
    }
    const auto finish{std::chrono::high_resolution_clock::now()};
    double elapsed_time{std::chrono::duration<double, std::milli>(finish - start).count() / static_cast<double>(repeats)};
    
    std::cout << "Duration: " << elapsed_time << " ms \n";
}

int main() {
    const int n{40};
    const int repeats{5};

    Benchmark(FibNoThreading, n, repeats);
    Benchmark(pthreadParallelFib, n, repeats);
    Benchmark(CppParallel, n, repeats);
    Benchmark(OpenmpParallel, n, repeats);

    return 0;
}

static int OpenmpFib(const int n) {
    int x, y;
    if(n < 2) {
        return n;
    } else {

    #pragma omp task shared(x)
        x = Fib(n - 1);
    #pragma omp task shared(y)
        y = Fib(n - 2);

    #pragma omp taskwait
        return x + y;
    }
}

void OpenmpParallel(const int n) {
    int result{0};

    #pragma omp parallel
    {
        #pragma omp single
        result = OpenmpFib(n);
    }

    std::cout << "Fib of " << n << " is: " << result << "\n";    
}

void CppParallel(const int n) {
    auto future{std::async(Fib, n - 1)};
    int thrd_1_res{Fib(n - 2)};
    int thrd_2_res{future.get()};

    std::cout << "Fib of " << n << " is: " << thrd_1_res + thrd_2_res << "\n";
}

void pthreadParallelFib(const int n) {
    pthread_t thread;
    thread_args args;
    int result1{0};

    args.input = n - 1;
    pthread_create(&thread, NULL, ThreadFunc, static_cast<void*>(&args));
    result1 = Fib(n - 2);
    pthread_join(thread, NULL);

    result1 += args.output;

    std::cout << "Fib of " << n << " is: " << result1 << "\n";
}

int Fib(int n) {
    if (n < 2) {
        return n;
    } else {
        int x{Fib(n - 1)};
        int y{Fib(n - 2)};
        return x + y;
    }
}

void FibNoThreading(const int n) {
    Fib(n);
}

void* ThreadFunc(void* ptr) {
    int i{static_cast<thread_args*>(ptr)->input};
    static_cast<thread_args*>(ptr)->output = Fib(i);
    return NULL;
}

