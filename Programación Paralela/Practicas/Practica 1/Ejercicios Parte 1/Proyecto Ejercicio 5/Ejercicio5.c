#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int reducir_vector(int* vector, int n) {
    int suma = 0;

    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < n; i++) {
        suma += vector[i];
    }

    return suma;
}

int main() {
    int tamaños[] = {1024, 2048, 4096};
    int num_procesos[] = {2, 4, 6, 8};

    for (int i = 0; i < sizeof(tamaños) / sizeof(tamaños[0]); i++) {
        int n = tamaños[i];
        int* vector = (int*)malloc(n * sizeof(int));

        // Inicializar vector
        for (int j = 0; j < n; j++) {
            vector[j] = j;
        }

        printf("Tamaño del vector: %d\n", n);

        for (int k = 0; k < sizeof(num_procesos) / sizeof(num_procesos[0]); k++) {
            int num_procs = num_procesos[k];
            omp_set_num_threads(num_procs);

            double start_time = omp_get_wtime();

            int suma = reducir_vector(vector, n);

            double end_time = omp_get_wtime();
            double elapsed_time = end_time - start_time;

            printf("Número de procesos: %d, Suma: %d, Tiempo de ejecución: %f segundos\n", num_procs, suma, elapsed_time);

            free(vector);
        }
    }
    
    return 0;
}