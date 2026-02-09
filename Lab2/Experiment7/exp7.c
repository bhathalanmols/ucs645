#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long N = 100000000;
    double *A = malloc(N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *C = malloc(N * sizeof(double));
    double scalar = 3.14;

    for (long i = 0; i < N; i++) {
        B[i] = 1.0;
        C[i] = 2.0;
    }

    int max_threads = omp_get_max_threads();
    double start, end;

    printf("Threads\tTime(s)\tBandwidth(GB/s)\n");

    for (int t = 1; t <= max_threads; t *= 2) {
        start = omp_get_wtime();

        #pragma omp parallel for num_threads(t)
        for (long i = 0; i < N; i++) {
            A[i] = B[i] + scalar * C[i];
        }

        end = omp_get_wtime();

        double time = end - start;
        double bandwidth = (3.0 * N * sizeof(double)) / (time * 1e9);

        printf("%d\t%f\t%f\n", t, time, bandwidth);
    }

    free(A); free(B); free(C);
    return 0;
}
