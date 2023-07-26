#include <stdio.h>

#define N (1024*1024)
#define TAMBLOCK 16

__global__ void sumaMatrices(float *d_a, float *d_b, float *d_c, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n && col < n) {
        d_c[row * n + col] = d_a[row * n + col] + d_b[row * n + col];
    }
}

int main() {
    float *h_a, *h_b, *h_c;
    float *d_a, *d_b, *d_c;
    int size = N * sizeof(float);

    h_a = (float*)malloc(size);
    h_b = (float*)malloc(size);
    h_c = (float*)malloc(size);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            h_a[i * N + j] = i + j;
            h_b[i * N + j] = i - j;
        }
    }

    cudaMalloc((void**)&d_a, size);
    cudaMalloc((void**)&d_b, size);
    cudaMalloc((void**)&d_c, size);

    cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

    dim3 block(TAMBLOCK, TAMBLOCK);
    dim3 grid((N + TAMBLOCK - 1) / TAMBLOCK, (N + TAMBLOCK - 1) / TAMBLOCK);

    sumaMatrices<<<grid, block>>>(d_a, d_b, d_c, N);

    cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

    printf("Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", h_c[i * N + j]);
        }
        printf("\n");
    }

    free(h_a);
    free(h_b);
    free(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}