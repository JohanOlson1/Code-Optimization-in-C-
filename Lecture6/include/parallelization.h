#ifndef LECTURE_6_MAIN_H
#define LECTURE_6_MAIN_H

typedef struct {
    int input;
    int output;
} thread_args;

void OpenmpParallel(const int n);

void CppParallel(const int n);

void pthreadParallelFib(const int n);

int Fib(int n);

void FibNoThreading(const int n);

void* ThreadFunc(void* ptr);

#endif // LECTURE_6_MAIN_H