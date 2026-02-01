#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 65536

int main() {
    double *X = malloc(N*sizeof(double));
    double *Y = malloc(N*sizeof(double));
    double a = 2.0;

    for(int i=0;i<N;i++){
        X[i] = 1.0;
        Y[i] = 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for(int i=0;i<N;i++){
        X[i] = a * X[i] + Y[i];
    }

    double end = omp_get_wtime();
    printf("DAXPY Time: %f\n", end-start);

    return 0;
}
