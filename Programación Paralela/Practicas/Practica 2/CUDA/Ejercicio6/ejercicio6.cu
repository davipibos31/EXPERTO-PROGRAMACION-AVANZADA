#include <cuda_runtime.h>
#include <stdio.h>

#define N 1024
#define EPSILON 0.0001

//@Rellenar: Kernel que implementa el método de Jacobi
__global__ void jacobi(float *d_A, float *d_B, float *d_C)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row > 0 && row < N - 1 && col > 0 && col < N - 1)
    {
        d_C[row * N + col] = 0.2f * (d_B[row * N + col] + d_A[(row - 1) * N + col] + d_A[row * N + col - 1] + d_A[(row + 1) * N + col] + d_A[row * N + col + 1]);
    }
}

//@Rellenar: Función para inicializar las matrices A y B
void initializeMatrices(float *h_A, float *h_B)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == 0 || i == N - 1 || j == 0 || j == N - 1)
            {
                h_A[i * N + j] = 0.0f;  // Valores fijos en los límites
                h_B[i * N + j] = 0.0f;
            }
            else
            {
                h_A[i * N + j] = 1.0f;  // Valor inicial arbitrario en el interior
                h_B[i * N + j] = 1.0f;
            }
        }
    }
}

//@Rellenar: Función para imprimir una matriz
void printMatrix(float *matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.2f ", matrix[i * N + j]);
        }
        printf("\n");
    }
}

//@Rellenar: Función para verificar la convergencia del método
int checkConvergence(float *h_A, float *h_B)
{
    for (int i = 1; i < N - 1; i++)
    {
        for (int j = 1; j < N - 1; j++)
        {
            if (fabs(h_A[i * N + j] - h_B[i * N + j]) > EPSILON)
            {
                return 0;  // No ha convergido
            }
        }
    }
    return 1;  // Ha convergido
}

int main(int argc, char **argv)
{
    float *h_A = (float *)malloc(N * N * sizeof(float));
    float *h_B = (float *)malloc(N * N * sizeof(float));
    float *d_A;
    float *d_B;
    float *temp;

    //@Rellenar: Indica el tamaño de bloque en hilos.
    dim3 block(16, 16);
    //@Rellenar: Parámetros del kernel. Hilos por bloque, bloques por Grid.
    dim3 grid((N + block.x - 1) / block.x, (N + block.y - 1) / block.y);

    cudaMalloc((void **)&d_A, N * N * sizeof(float));
    cudaMalloc((void **)&d_B, N * N * sizeof(float));

    initializeMatrices(h_A, h_B);
    cudaMemcpy(d_A, h_A, N * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, N * N * sizeof(float), cudaMemcpyHostToDevice);

    int iterations = 0;
    while (!checkConvergence(h_A, h_B))
    {
        jacobi<<<grid, block>>>(d_A, d_B, d_A);
        iterations++;
        temp = d_A;
        d_A = d_B;
        d_B = temp;
    }

    cudaMemcpy(h_A, d_A, N * N * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Converged after %d iterations.\n", iterations);
    printf("Final matrix:\n");
    printMatrix(h_A);

    free(h_A);
    free(h_B);
    cudaFree(d_A);
    cudaFree(d_B);

    return 0;
}
