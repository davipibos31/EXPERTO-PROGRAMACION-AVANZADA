#include <assert.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdlib.h>
#include <stdio.h>


#define N 16384
#define TAMBLOCK 256
#define NUMITER 4096 //numero de iteraciones
__global__ void stencil1D(float *d_a, float *d_b){
	
	int indice = blockIdx.x * blockDim.x + threadIdx.x;

	if (indice > 0 && indice < (N-1))
	d_b[indice] = (d_a[indice] + d_a[indice - 1] + d_a[indice + 1])/3.0f;
	
}


int main()
{
	float *h_a, *h_b;
	float *d_a, *d_b;
	int memsize = N*sizeof(float);
    cudaError_t cudaStatus;

    // Choose which GPU to run on, change this on a multi-GPU system.
    cudaStatus = cudaSetDevice(0);

	h_a = (float *)malloc(memsize);

	if (h_a == NULL){
		fprintf(stderr,"Error al reservar memoria en el host\n");
		return EXIT_FAILURE;
	}

	h_b = (float *)malloc(memsize);

	if (h_b == NULL){
		fprintf(stderr, "Error al reservar memoria en el host\n");
		return EXIT_FAILURE;
	}

	cudaStatus = cudaMalloc(&d_a, memsize);
	if (cudaStatus != cudaSuccess){
		fprintf(stderr, "Error al reservar memoria en el device\n");
		return EXIT_FAILURE;
	}

	cudaStatus = cudaMalloc(&d_b, memsize);
	if (cudaStatus != cudaSuccess){
		fprintf(stderr, "Error al reservar memoria en el device\n");
		return EXIT_FAILURE;
	}

	//los bordes deberiamos de haberlos inicialilzado (h_b más que nada porque en el array el primer hueco no hay nada): 150 70 70 70 ... 70 150
	h_a[0] = h_a[N-1] = 150.0f; /*No inicializo h_b por que estaría copiando todo el rato*/
	for (int i = 1; i < (N-1); ++i){
		h_a[i] = 70.0f;
	}

	cudaStatus = cudaMemcpy(d_a, h_a, memsize, cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess){
		fprintf(stderr, "Error al transferir memoria al device\n");
		return EXIT_FAILURE;
	}

	cudaStatus = cudaMemcpy(d_b, h_a, memsize, cudaMemcpyHostToDevice);

	if (cudaStatus != cudaSuccess){
		fprintf(stderr, "Error al transferir memoria al device\n");
		return EXIT_FAILURE;
	}

	cudaEvent_t start, stop; 

	cudaEventCreate(&start, NULL);
	cudaEventCreate(&stop, NULL);

	dim3 block(N/TAMBLOCK);
	dim3 hilos(TAMBLOCK);

	float *aux = NULL; 
	cudaEventRecord(start, 0);
	for (int i = 0; i < NUMITER; ++i) {
		stencil1D<<<block, hilos>>>(d_a, d_b);
		//cudaThreadSynchronize();
		aux = d_a;
		d_a = d_b;
		d_b = aux; 
	}
	cudaEventRecord (stop, 0);
	cudaEventSynchronize(stop);
	float msec =0.0f;
	cudaEventElapsedTime(&msec, start, stop);
	printf ("El tiempo de ejecucion es %f msec\n", msec);

	cudaMemcpy (h_a, d_a, memsize, cudaMemcpyDeviceToHost);
	/*for (int i = 0; i<N; ++i) {
			printf ("%f, ", h_a[i]);
		}
		printf ("\n");
	*/

	 
    cudaFree(d_a);
    cudaFree(d_b);
	free (h_a);
	free (h_b);
 
	system ("PAUSE");
    return cudaStatus;
}
