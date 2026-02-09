#include <stdio.h>
#include <omp.h>

static long steps = 1000000;

int main() {
    double sum = 0.0;
    double step = 1.0 / steps;

    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    printf("PI = %f\n", step * sum);
    return 0;
}

