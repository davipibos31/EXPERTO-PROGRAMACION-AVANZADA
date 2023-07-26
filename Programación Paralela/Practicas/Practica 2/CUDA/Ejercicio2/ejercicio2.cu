#include <cuda_runtime.h>
#include <stdio.h>

#define N 1024
#define TILE_SIZE 256

__global__ void saxpy(float alpha, float* x, float* y, float* result)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < N)
        result[i] = alpha * x[i] + y[i];
}

int main()
{
    float alpha = 2.0f;
    float* h_x = (float*)malloc(N * sizeof(float));
    float* h_y = (float*)malloc(N * sizeof(float));
    float* h_result = (float*)malloc(N * sizeof(float));
    float* d_x;
    float* d_y;
    float* d_result;

    for (int i = 0; i < N; i++)
    {
        h_x[i] = i;
        h_y[i] = i + 1;
    }

    cudaMalloc((void**)&d_x, N * sizeof(float));
    cudaMalloc((void**)&d_y, N * sizeof(float));
    cudaMalloc((void**)&d_result, N * sizeof(float));

    cudaMemcpy(d_x, h_x, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, h_y, N * sizeof(float), cudaMemcpyHostToDevice);

    dim3 block(TILE_SIZE);
    dim3 grid((N + TILE_SIZE - 1) / TILE_SIZE);

    saxpy<<<grid, block>>>(alpha, d_x, d_y, d_result);

    cudaMemcpy(h_result, d_result, N * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < N; i++)
        printf("result[%d] = %.2f\n", i, h_result[i]);

    free(h_x);
    free(h_y);
    free(h_result);
    cudaFree(d_x);
    cudaFree(d_y);
    cudaFree(d_result);

    return 0;
}
