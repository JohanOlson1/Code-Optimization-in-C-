#ifndef LECTURE_6_MAIN_H
#define LECTURE_6_MAIN_H

typedef struct {
    int input;
    int output;
} thread_args;

void pthread_parallel_fib(const int n);

int fib(int n);

void* thread_func(void* ptr);

#endif // LECTURE_6_MAIN_H