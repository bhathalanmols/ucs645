#include <stdio.h>
#include <omp.h>

#define N 300

int main() {
    static int A[N][N], B[N][N], C[N][N];

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            A[i][j] = B[i][j] = 1;

    #pragma omp parallel for
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            C[i][j] = 0;
            for(int k=0;k<N;k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    printf("Matrix multiplication completed\n");
    return 0;
}
