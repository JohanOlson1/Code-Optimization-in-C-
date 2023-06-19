#ifndef LECTURE_6_MAIN_H
#define LECTURE_6_MAIN_H

typedef struct {
    int input;
    int output;
} thread_args;

void openMPParallel(const int n);

void cppParallel(const int n);

void pthreadParallelFib(const int n);

int fib(int n);

void* threadFunc(void* ptr);

#endif // LECTURE_6_MAIN_H