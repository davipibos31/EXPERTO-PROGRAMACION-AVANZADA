#include <cuda_runtime.h>
#include <stdio.h>

#define N 1024
#define TILE_SIZE 256

__global__ void stencil1D(float* y, float* result)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int tx = threadIdx.x;

    __shared__ float tile[TILE_SIZE + 2];

    int ti = tx + 1;
    if (i >= N)
        tile[ti] = 0.0f;
    else
        tile[ti] = y[i];

    if (tx == 0)
        tile[ti - 1] = (i > 0) ? y[i - 1] : 0.0f;

    if (tx == blockDim.x - 1)
        tile[ti + 1] = (i < N - 1) ? y[i + 1] : 0.0f;

    __syncthreads();

    if (i < N)
        result[i] = (tile[ti - 1] * tile[ti] * tile[ti + 1]) / 3;
}

int main()
{
    float* h_y = (float*)malloc(N * sizeof(float));
    float* h_result = (float*)malloc(N * sizeof(float));
    float* d_y;
    float* d_result;

    for (int i = 0; i < N; i++)
        h_y[i] = i + 1;

    cudaMalloc((void**)&d_y, N * sizeof(float));
    cudaMalloc((void**)&d_result, N * sizeof(float));

    cudaMemcpy(d_y, h_y, N * sizeof(float), cudaMemcpyHostToDevice);

    dim3 block(TILE_SIZE);
    dim3 grid((N + TILE_SIZE - 1) / TILE_SIZE);

    stencil1D<<<grid, block>>>(d_y, d_result);

    cudaMemcpy(h_result, d_result, N * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < N; i++)
        printf("y[%d] = %.2f\n", i, h_result[i]);

    free(h_y);
    free(h_result);
    cudaFree(d_y);
    cudaFree(d_result);

    return 0;
}
