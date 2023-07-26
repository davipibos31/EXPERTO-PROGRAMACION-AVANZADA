#include <cuda_runtime.h>
#include <stdio.h>

#define N 1024
#define TILE_SIZE 256

__global__ void reductionSum(int* input, int* output)
{
    __shared__ int sharedData[TILE_SIZE];

    int tid = threadIdx.x;
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    sharedData[tid] = (i < N) ? input[i] : 0;

    __syncthreads();

    for (unsigned int s = blockDim.x / 2; s > 0; s >>= 1)
    {
        if (tid < s)
            sharedData[tid] += sharedData[tid + s];

        __syncthreads();
    }

    if (tid == 0)
        output[blockIdx.x] = sharedData[0];
}

int main()
{
    int* h_input = (int*)malloc(N * sizeof(int));
    int* h_output = (int*)malloc(N * sizeof(int));
    int* d_input;
    int* d_output;

    for (int i = 0; i < N; i++)
        h_input[i] = i + 1;

    cudaMalloc((void**)&d_input, N * sizeof(int));
    cudaMalloc((void**)&d_output, N * sizeof(int));

    cudaMemcpy(d_input, h_input, N * sizeof(int), cudaMemcpyHostToDevice);

    dim3 block(TILE_SIZE);
    dim3 grid((N + TILE_SIZE - 1) / TILE_SIZE);

    reductionSum<<<grid, block>>>(d_input, d_output);

    cudaMemcpy(h_output, d_output, grid.x * sizeof(int), cudaMemcpyDeviceToHost);

    int sum = 0;
    for (int i = 0; i < grid.x; i++)
        sum += h_output[i];

    printf("Sum: %d\n", sum);

    free(h_input);
    free(h_output);
    cudaFree(d_input);
    cudaFree(d_output);

    return 0;
}
