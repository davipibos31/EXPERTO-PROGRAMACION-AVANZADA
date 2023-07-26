#include <cuda_runtime.h>
#include <stdio.h>

#define N (1024)
#define TILE_SIZE 16

//@Rellenar: Kernel que desarrolla la suma de dos matrices
__global__ void sumaMatrices(float *d_a, float *d_b, float *d_c)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    d_c[row * N + col] = d_a[row * N + col] + d_b[row * N + col];
}

int main(int argc, char **argv)
{
    float *h_a = (float *)malloc(N * N * sizeof(float));
    float *h_b = (float *)malloc(N * N * sizeof(float));
    float *h_c = (float *)malloc(N * N * sizeof(float));
    float *d_a;
    float *d_b;
    float *d_c;

    //@Rellenar: Indica el tamaño de bloque en hilos.
    dim3 block(TILE_SIZE, TILE_SIZE);
    //@Rellenar: Parámetros del kernel. Hilos por bloque, bloques por Grid.
    dim3 grid((N + TILE_SIZE - 1) / TILE_SIZE, (N + TILE_SIZE - 1) / TILE_SIZE);

    cudaMalloc((void **)&d_a, N * N * sizeof(float));
    cudaMalloc((void **)&d_b, N * N * sizeof(float));
    cudaMalloc((void **)&d_c, N * N * sizeof(float));

    // Inicializar matrices h_a y h_b
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            h_a[i * N + j] = i + j;
            h_b[i * N + j] = i - j;
        }
    }

    cudaMemcpy(d_a, h_a, N * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, N * N * sizeof(float), cudaMemcpyHostToDevice);

    //@Rellenar: Parámetros del kernel. Hilos por bloque, bloques por Grid.
    sumaMatrices<<<grid, block>>>(d_a, d_b, d_c);

    cudaMemcpy(h_c, d_c, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    // Imprimir matriz resultante h_c
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
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
