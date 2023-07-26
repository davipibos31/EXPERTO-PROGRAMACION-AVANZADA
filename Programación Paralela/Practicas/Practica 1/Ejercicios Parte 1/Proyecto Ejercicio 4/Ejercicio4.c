#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void saxpy(float* x, float* y, float alpha, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        y[i] = x[i] * alpha + y[i];
    }
}

int main() {
    int tamaños[] = {1024, 2048, 4096};
    int num_procesos[] = {2, 4, 6, 8};

    for (int i = 0; i < sizeof(tamaños) / sizeof(tamaños[0]); i++) {
        int n = tamaños[i];
        float* x = (float*)malloc(n * sizeof(float));
        float* y = (float*)malloc(n * sizeof(float));
        float alpha = 2.0;

        // Inicializar vectores x e y
        for (int j = 0; j < n; j++) {
            x[j] = j;
            y[j] = j;
        }

        printf("Tamaño del vector: %d\n", n);

        for (int k = 0; k < sizeof(num_procesos) / sizeof(num_procesos[0]); k++) {
            int num_procs = num_procesos[k];

            omp_set_num_threads(num_procs);

            double start_time = omp_get_wtime();

            saxpy(x, y, alpha, n);

            double end_time = omp_get_wtime();
            double elapsed_time = end_time - start_time;

            printf("Número de procesos: %d, Tiempo de ejecución: %f segundos\n", num_procs, elapsed_time);

            free(x);
            free(y);
        }
    }

    return 0;
}