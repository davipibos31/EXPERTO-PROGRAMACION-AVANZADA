#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void sumar_vectores(int* a, int* b, int* c, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    int tamaños[] = {1024, 2048, 4096};
    int num_procesos[] = {2, 4, 6, 8};

    for (int i = 0; i < sizeof(tamaños) / sizeof(tamaños[0]); i++) {
        int n = tamaños[i];
        int* a = (int*)malloc(n * sizeof(int));
        int* b = (int*)malloc(n * sizeof(int));
        int* c = (int*)malloc(n * sizeof(int));

        // Inicializar vectores a y b
        for (int j = 0; j < n; j++) {
            a[j] = j;
            b[j] = j;
        }

        printf("Tamaño del vector: %d\n", n);

        for (int k = 0; k < sizeof(num_procesos) / sizeof(num_procesos[0]); k++) {
            int num_procs = num_procesos[k];

            omp_set_num_threads(num_procs);

            double start_time = omp_get_wtime();

            sumar_vectores(a, b, c, n);

            double end_time = omp_get_wtime();
            double elapsed_time = end_time - start_time;

            printf("Número de procesos: %d, Tiempo de ejecución: %f segundos\n", num_procs, elapsed_time);

            free(a);
            free(b);
            free(c);
        }
    }

    return 0;
}
