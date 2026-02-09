#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long N = 100000000;   // 100 million elements

    double *A = (double*) malloc(N * sizeof(double));
    double *B = (double*) malloc(N * sizeof(double));
    double *C = (double*) malloc(N * sizeof(double));

    for (long i = 0; i < N; i++) {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (long i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    double end = omp_get_wtime();

    printf("Execution Time = %f seconds\n", end - start);

    free(A);
    free(B);
    free(C);

    return 0;
}
