#include <iostream>
#include <cuda_runtime.h>

int main()
{
  // Reserva e inicializa memoria en la CPU
  float *h_A = new float[N], *h_B = new float[N];

  // Reserva memoria en la GPU
  float *d_A, *d_B, *d_C;
  cudaMalloc((void**)&d_A, N * sizeof(float));
  cudaMalloc((void**)&d_B, N * sizeof(float));
  cudaMalloc((void**)&d_C, N * sizeof(float));

  // Copia host memory en device
  cudaMemcpy(d_A, h_A, N * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B, N * sizeof(float), cudaMemcpyHostToDevice);

  // Ejecuta el kernel en ceil(N/256) blocks de 256 threads cada uno
  vecAdd<<<ceil(N/256.0), 256>>>(d_A, d_B, d_C, N);

  // Copia el resultado de vuelta a la CPU
  cudaMemcpy(h_C, d_C, N * sizeof(float), cudaMemcpyDeviceToHost);

  // Libera memoria de la GPU
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);

  // Libera memoria de la CPU
  delete[] h_A;
  delete[] h_B;

  return 0;
}
