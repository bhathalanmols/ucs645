#include <stdio.h>
#include <omp.h>

int main() {
    long long N = 10000000;
    double sum_critical = 0.0;
    double sum_reduction = 0.0;
    double start, end;

    /* -------- CRITICAL SECTION -------- */
    start = omp_get_wtime();
    #pragma omp parallel for
    for (long long i = 0; i < N; i++) {
        #pragma omp critical
        {
            sum_critical += 1.0;
        }
    }
    end = omp_get_wtime();
    printf("Critical Section Time: %f seconds\n", end - start);

    /* -------- REDUCTION -------- */
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_reduction)
    for (long long i = 0; i < N; i++) {
        sum_reduction += 1.0;
    }
    end = omp_get_wtime();
    printf("Reduction Time: %f seconds\n", end - start);

    return 0;
}
