#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1024

void jacobi_sequential(double A[N][N], double A_new[N][N]) {
    int i, j;

    for (i = 1; i < N - 1; i++) {
        for (j = 1; j < N - 1; j++) {
            A_new[i][j] = 0.25 * (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]);
        }
    }
}

void jacobi_parallel1(double A[N][N], double A_new[N][N]) {
    int i, j;

    #pragma omp parallel for private(i, j) shared(A, A_new)
    for (i = 1; i < N - 1; i++) {
        for (j = 1; j < N - 1; j++) {
            A_new[i][j] = 0.25 * (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]);
        }
    }
}

void jacobi_parallel2(double A[N][N], double A_new[N][N]) {
    int i, j;

    #pragma omp parallel for collapse(2) private(i, j) shared(A, A_new)
    for (i = 1; i < N - 1; i++) {
        for (j = 1; j < N - 1; j++) {
            A_new[i][j] = 0.25 * (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]);
        }
    }
}

int main() {
    double A[N][N], A_new[N][N];
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
    jacobi_sequential(A, A_new);
    end_time = omp_get_wtime();
    printf("Sequential execution time: %f seconds\n", end_time - start_time);

    // Parallel execution 1
    start_time = omp_get_wtime();
    jacobi_parallel1(A, A_new);
    end_time = omp_get_wtime();
    printf("Parallel execution 1 time: %f seconds\n", end_time - start_time);

    // Parallel execution 2
    start_time = omp_get_wtime();
    jacobi_parallel2(A, A_new);
    end_time = omp_get_wtime();
    printf("Parallel execution 2 time: %f seconds\n", end_time - start_time);

    return 0;
}
