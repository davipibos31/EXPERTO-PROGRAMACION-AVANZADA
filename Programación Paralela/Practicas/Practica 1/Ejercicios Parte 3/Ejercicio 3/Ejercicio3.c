#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1024
#define ITERATIONS 100

void stencil_sequential(double A[N][N], double B[N][N]) {
    int i, j, k;

    for (k = 0; k < ITERATIONS; k++) {
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                B[i][j] = A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1];
            }
        }

        // Swap A and B
        double (*temp)[N] = A;
        A = B;
        B = temp;
    }
}

void stencil_parallel(double A[N][N], double B[N][N]) {
    int i, j, k;

    for (k = 0; k < ITERATIONS; k++) {
        #pragma omp parallel for private(i, j) shared(A, B)
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                B[i][j] = A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1];
            }
        }

        // Swap A and B
        double (*temp)[N] = A;
        A = B;
        B = temp;
    }
}

int main() {
    double A[N][N], B[N][N];
    int i, j;
    double start_time, end_time;

    // Initialize A with some values

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
        }
    }

    // Sequential execution
    start_time = omp_get_wtime();
    stencil_sequential(A, B);
    end_time = omp_get_wtime();
    printf("Sequential execution time: %f seconds\n", end_time - start_time);

    // Parallel execution
    start_time = omp_get_wtime();
    stencil_parallel(A, B);
    end_time = omp_get_wtime();
    printf("Parallel execution time: %f seconds\n", end_time - start_time);

    return 0;
}
