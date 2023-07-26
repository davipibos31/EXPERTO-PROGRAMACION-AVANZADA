#include <stdio.h>

#define N 1024
#define MAX_ITERATIONS 1000

void jacobi(float* A, float* B) {
    for (int k = 0; k < MAX_ITERATIONS; k++) {
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                B[i * N + j] = 0.2f * (A[i * N + j] + A[(i - 1) * N + j] + A[i * N + (j - 1)] + A[(i + 1) * N + j] + A[i * N + (j + 1)]);
            }
        }
        float* temp = A;
        A = B;
        B = temp;
    }
}

int main() {
    float* A = (float*)malloc(N * N * sizeof(float));
    float* B = (float*)malloc(N * N * sizeof(float));

    // Initialize A with initial temperature values

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = 0.0f;
        }
    }

    // Set boundary conditions
    for (int i = 0; i < N; i++) {
        A[i * N] = 100.0f;
        A[i * N + (N - 1)] = 100.0f;
        A[i] = 100.0f;
        A[(N - 1) * N + i] = 100.0f;
    }

    // Perform Jacobi iterations
    jacobi(A, B);

    // Print final temperature values
    printf("Final Temperature Values:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", A[i * N + j]);
        }
        printf("\n");
    }

    free(A);
    free(B);

    return 0;
}
