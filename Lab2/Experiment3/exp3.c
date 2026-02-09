#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int threads;
    long N;
    double start, end;

    /* -------- STRONG SCALING -------- */
    N = 100000000;

    printf("STRONG SCALING (Fixed N = %ld)\n", N);

    for (threads = 1; threads <= 8; threads *= 2) {
        double *A = malloc(N * sizeof(double));
        double *B = malloc(N * sizeof(double));
        double *C = malloc(N * sizeof(double));

        start = omp_get_wtime();

        #pragma omp parallel for num_threads(threads)
        for (long i = 0; i < N; i++) {
            C[i] = A[i] + B[i];
        }

        end = omp_get_wtime();

        printf("Threads: %d | Time: %f seconds\n", threads, end - start);

        free(A); free(B); free(C);
    }

    /* -------- WEAK SCALING -------- */
    printf("\nWEAK SCALING (N increases with threads)\n");

    for (threads = 1; threads <= 8; threads *= 2) {
        N = 100000000 * threads;

        double *A = malloc(N * sizeof(double));
        double *B = malloc(N * sizeof(double));
        double *C = malloc(N * sizeof(double));

        start = omp_get_wtime();

        #pragma omp parallel for num_threads(threads)
        for (long i = 0; i < N; i++) {
            C[i] = A[i] + B[i];
        }

        end = omp_get_wtime();

        printf("Threads: %d | N: %ld | Time: %f seconds\n",
               threads, N, end - start);

        free(A); free(B); free(C);
    }

    return 0;
}
