#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1024

void matrix_multiply_sequential(double A[N][N], double B[N][N], double C[N][N]) {
    int i, j, k;
    double sum;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0.0;
            for (k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}

void matrix_multiply_parallel(double A[N][N], double B[N][N], double C[N][N]) {
    int i, j, k;
    double sum;

    #pragma omp parallel for private(i, j, k, sum) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0.0;
            for (k = 0; k < N; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}

int main() {
    double A[N][N], B[N][N], C[N][N];
    int i, j;
    double start_time, end_time;

    // Initialize A and B with some values

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Sequential execution
    start_time = omp_get_wtime();
    matrix_multiply_sequential(A, B, C);
    end_time = omp_get_wtime();
    printf("Sequential execution time: %f seconds\n", end_time - start_time);

    // Parallel execution
    start_time = omp_get_wtime();
    matrix_multiply_parallel(A, B, C);
    end_time = omp_get_wtime();
    printf("Parallel execution time: %f seconds\n", end_time - start_time);

    return 0;
}
