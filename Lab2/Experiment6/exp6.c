#include <stdio.h>
#include <omp.h>

#define CACHE_LINE 64

typedef struct {
    long long value;
} bad_struct;

typedef struct {
    long long value;
    char padding[CACHE_LINE - sizeof(long long)];
} good_struct;

int main() {
    int threads = omp_get_max_threads();
    long long iterations = 100000000;

    bad_struct bad[threads];
    good_struct good[threads];

    double start, end;

    /* -------- FALSE SHARING -------- */
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (long long i = 0; i < iterations; i++) {
            bad[tid].value++;
        }
    }
    end = omp_get_wtime();
    printf("False Sharing Time: %f seconds\n", end - start);

    /* -------- PADDED (NO FALSE SHARING) -------- */
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (long long i = 0; i < iterations; i++) {
            good[tid].value++;
        }
    }
    end = omp_get_wtime();
    printf("Padded Time: %f seconds\n", end - start);

    return 0;
}
