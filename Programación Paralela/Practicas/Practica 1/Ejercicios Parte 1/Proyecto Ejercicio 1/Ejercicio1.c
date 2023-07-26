#include <stdio.h>
#include <omp.h>

int main() {
    int num_hilos;
    printf("Ingrese el número de hilos a ejecutar: ");
    scanf("%d", &num_hilos);

    omp_set_num_threads(num_hilos);

    #pragma omp parallel
    {
        int num_hilos_actual = omp_get_num_threads();
        int id_hilo = omp_get_thread_num();

        #pragma omp master
        {
            printf("Número de hilos en ejecución: %d\n", num_hilos_actual);
        }

        printf("Identificador de hilo: %d\n", id_hilo);
    }

    return 0;
}
