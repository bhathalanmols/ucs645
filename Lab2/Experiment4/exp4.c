#include <stdio.h>
#include <omp.h>
#include <math.h>

void work(int i) {
    double sum = 0;
    for (long j = 0; j < i * 50000; j++) {
        sum += sin(j);
    }
}

int main() {
    int N = 1000;
    double start, end;

    printf("STATIC SCHEDULING\n");
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        work(i);
    }
    end = omp_get_wtime();
    printf("Time (static): %f seconds\n\n", end - start);

    printf("DYNAMIC SCHEDULING\n");
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 10)
    for (int i = 0; i < N; i++) {
        work(i);
    }
    end = omp_get_wtime();
    printf("Time (dynamic): %f seconds\n", end - start);

    return 0;
}
