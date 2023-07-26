#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ejercicio5v2.h"

int comparaciones = 0; // Variable global para contar comparaciones
int intercambios = 0; // Variable global para contar intercambios

// Función para mostrar el arreglo en la consola
void mostrar_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void medir_tiempo_ejecucion(void (*algoritmo)(int[], int, int), int arr[], int n, const char *nombre_algoritmo) {
    clock_t inicio = clock();
    algoritmo(arr, 0, n - 1);
    clock_t fin = clock();
    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución (%s): %.6f segundos\n", nombre_algoritmo, tiempo);
}

// Función de contador para el número de comparaciones e intercambios
void contador() {
    comparaciones++;
    intercambios++;
}

void medir_comparaciones_intercambios(void (*algoritmo)(int[], int, int), int arr[], int n, const char *nombre_algoritmo) {

    contador();

    algoritmo(arr, 0, n - 1);

    printf("Comparaciones realizadas (%s): %d\n", nombre_algoritmo, comparaciones);
    printf("Intercambios realizados (%s): %d\n", nombre_algoritmo, intercambios);
}

// Función principal
int main() {
    const char *archivos[] = {"numeros50000.txt", "numeros100000.txt", "numeros200000.txt"};
    const int tamanios[] = {50000, 100000, 200000};
    const int num_archivos = sizeof(archivos) / sizeof(archivos[0]);

    srand(time(NULL)); // Inicializar la semilla aleatoria

    // Algoritmo de Burbuja
    printf("Algoritmo de Burbuja:\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));

        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(burbuja, arr, n, "Burbuja");
        medir_comparaciones_intercambios(burbuja, arr, n, "Burbuja");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "burbuja_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo de Burbuja Mejorada
    printf("Algoritmo de Burbuja Mejorada:\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));

        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(burbuja_mejorada, arr, n, "Burbuja Mejorada");
        medir_comparaciones_intercambios(burbuja_mejorada, arr, n, "Burbuja Mejorada");
            // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "burbuja_mejorada_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo de Selección Directa
    printf("Algoritmo de Selección Directa:\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));

        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(seleccion_directa, arr, n, "Selección Directa");
        medir_comparaciones_intercambios(seleccion_directa, arr, n, "Selección Directa");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "seleccion_directa_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo Shell
    printf("Algoritmo Shell:\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));

        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(shell_sort, arr, n, "Shell");
        medir_comparaciones_intercambios(shell_sort, arr, n, "Shell");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "shell_sort_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo QuickSort (Pivote: Valor en la posición del medio)
    printf("Algoritmo QuickSort (Pivote: Valor en la posición del medio):\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));

        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(quicksort_medio, arr, n, "QuickSort (Pivote: Valor en la posición del medio)");
        medir_comparaciones_intercambios(quicksort_medio, arr, n, "QuickSort (Pivote: Valor en la posición del medio)");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "quicksort_medio_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo QuickSort (Pivote: Aleatorio)
    printf("Algoritmo QuickSort (Pivote: Aleatorio):\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));
        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(quicksort_aleatorio, arr, n, "QuickSort (Pivote: Aleatorio)");
        medir_comparaciones_intercambios(quicksort_aleatorio, arr, n, "QuickSort (Pivote: Aleatorio)");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "quicksort_aleatorio_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo QuickSort (Pivote: Mediana utilizando el primer, último y medio elemento)
    printf("Algoritmo QuickSort (Pivote: Mediana utilizando el primer, último y medio elemento):\n");
    for (int i = 0; i < num_archivos; i++) {
        int n = tamanios[i];
        int *arr = malloc(n * sizeof(int));

        cargar_arreglo(arr, n, archivos[i]);

        printf("Archivo: %s\n", archivos[i]);
        medir_tiempo_ejecucion(quicksort_mediana, arr, n, "QuickSort (Pivote: Mediana utilizando el primer, último y medio elemento)");
        medir_comparaciones_intercambios(quicksort_mediana, arr, n, "QuickSort (Pivote: Mediana utilizando el primer, último y medio elemento)");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "quicksort_mediana_%s", archivos[i]);
        guardar_arreglo(arr, n, archivo_ordenado);

        free(arr);
    }

    // Algoritmo de Ordenación Bucket
        printf("Algoritmo de Ordenación Bucket:\n");
        for (int i = 0; i < num_archivos; i++) {
            int n = tamanios[i];
            int *arr = malloc(n * sizeof(int));

            cargar_arreglo(arr, n, archivos[i]);

            printf("Archivo: %s\n", archivos[i]);
            medir_tiempo_ejecucion(ordenacion_bucket, arr, n, "Ordenación Bucket");
            medir_comparaciones_intercambios(ordenacion_bucket, arr, n, "Ordenación Bucket");

            // Guardar el arreglo ordenado en un nuevo archivo
            char archivo_ordenado[100];
            snprintf(archivo_ordenado, sizeof(archivo_ordenado), "bucket_%s", archivos[i]);
            guardar_arreglo(arr, n, archivo_ordenado);

            free(arr);
        }

        // Algoritmo de Mezcla Directa o Natural
        printf("Algoritmo de Mezcla Directa o Natural:\n");
        int n = tamanios[2]; // Tamaño del archivo numeros200000.txt
        int *arr = malloc(n * sizeof(int));
        cargar_arreglo(arr, n, archivos[2]); // Solo se utiliza el archivo numeros200000.txt

        printf("Archivo: %s\n", archivos[2]);
        medir_tiempo_ejecucion(mezcla_directa, arr, n, "Mezcla Directa o Natural");
        medir_comparaciones_intercambios(mezcla_directa, arr, n, "Mezcla Directa o Natural");

        // Guardar el arreglo ordenado en un nuevo archivo
        char archivo_ordenado[100];
        snprintf(archivo_ordenado, sizeof(archivo_ordenado), "mezcla_directa_%s", archivos[2]); guardar_arreglo(arr,n,archivo_ordenado);
        free(arr);

    return 0;
}
