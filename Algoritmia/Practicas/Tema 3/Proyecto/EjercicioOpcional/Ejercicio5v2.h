#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void cargar_arreglo(int arr[], int n, const char *archivo) {
    FILE *f = fopen(archivo, "r");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &arr[i]);
    }

    fclose(f);
}

void guardar_arreglo(int arr[], int n, const char *archivo) {
    FILE *f = fopen(archivo, "w");
    if (f == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", arr[i]);
    }

    fclose(f);
}

void imprimir_arreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Algoritmo de Burbuja
void burbuja(int arr[], int inicio, int fin) {
    int i, j;
    for (i = inicio; i <= fin; i++) {
        for (j = inicio; j <= fin - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                intercambiar(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Algoritmo de Burbuja Mejorada
void burbuja_mejorada(int arr[], int inicio, int fin) {
    int i, j;
    int intercambiado;

    for (i = inicio; i <= fin; i++) {
        intercambiado = 0;
        for (j = inicio; j <= fin - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                intercambiar(&arr[j], &arr[j + 1]);
                intercambiado = 1;
            }
        }
        if (intercambiado == 0) {
            break;
        }
    }
}

// Algoritmo de Selección Directa
void seleccion_directa(int arr[], int inicio, int fin) {
    int i, j, min_idx;
    for (i = inicio; i <= fin - 1; i++) {
        min_idx = i;
        for (j = i + 1; j <= fin; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        intercambiar(&arr[min_idx], &arr[i]);
    }
}

// Algoritmo Shell
void shell_sort(int arr[], int inicio, int fin) {
    int n = fin - inicio + 1;
    int brecha, i, j, temp;
    for (brecha = n / 2; brecha > 0; brecha /= 2) {
        for (i = brecha; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= brecha && arr[j - brecha] > temp; j -= brecha) {
                arr[j] = arr[j - brecha];
            }
            arr[j] = temp;
        }
    }
}

// Función para obtener el pivote en QuickSort
int obtener_pivote(int arr[], int inicio, int fin) {
    return arr[(inicio + fin) / 2];
}

// Algoritmo QuickSort (Pivote: Valor en la posición del medio)
void quicksort_medio(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int pivote = obtener_pivote(arr, inicio, fin);
        int i = inicio;
        int j = fin;

        while (i <= j) {
            while (arr[i] < pivote) {
                i++;
            }
            while (arr[j] > pivote) {
                j--;
            }
            if (i <= j) {
                intercambiar(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        if (inicio < j) {
            quicksort_medio(arr, inicio, j);
        }
        if (i < fin) {
            quicksort_medio(arr, i, fin);
        }
    }
}

// Algoritmo QuickSort (Pivote: Aleatorio)
void quicksort_aleatorio(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int pivote_idx = inicio + rand() % (fin - inicio + 1);
        int pivote = arr[pivote_idx];
        int i = inicio;
        int j = fin;

        while (i <= j) {
            while (arr[i] < pivote) {
                i++;
            }
            while (arr[j] > pivote) {
                j--;
            }
            if (i <= j) {
                intercambiar(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        if (inicio < j) {
            quicksort_aleatorio(arr, inicio, j);
        }
        if (i < fin) {
            quicksort_aleatorio(arr, i, fin);
        }
    }
}

// Función para obtener la mediana de tres elementos
int obtener_mediana(int a, int b, int c) {
    if (a <= b && b <= c) {
        return b;
    } else if (c <= b && b <= a) {
        return b;
    } else if (b <= a && a <= c) {
        return a;
    } else if (c <= a && a <= b) {
        return a;
    } else {
        return c;
    }
}

// Algoritmo QuickSort (Pivote: Mediana utilizando el primer, último y medio elemento)
void quicksort_mediana(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int primer_elemento = arr[inicio];
        int ultimo_elemento = arr[fin];
        int medio_idx = (inicio + fin) / 2;
        int medio_elemento = arr[medio_idx];
        int pivote = obtener_mediana(primer_elemento, ultimo_elemento, medio_elemento);
        int i = inicio;
        int j = fin;

        while (i <= j) {
            while (arr[i] < pivote) {
                i++;
            }
            while (arr[j] > pivote) {
                j--;
            }
            if (i <= j) {
                intercambiar(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        if (inicio < j) {
            quicksort_mediana(arr, inicio, j);
        }
        if (i < fin) {
            quicksort_mediana(arr, i, fin);
        }
    }
}

// Algoritmo de Ordenación Bucket
void ordenacion_bucket(int arr[], int n) {
    // Encontrar el valor máximo en el arreglo
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Crear un arreglo de listas (buckets) utilizando memoria dinámica
    int num_buckets = 10;
    int** buckets = malloc(num_buckets * sizeof(int*));
    int* bucket_sizes = malloc(num_buckets * sizeof(int));
    for (int i = 0; i < num_buckets; i++) {
        buckets[i] = malloc(n * sizeof(int));
        bucket_sizes[i] = 0;
    }

    // Colocar los elementos en los buckets correspondientes
    for (int i = 0; i < n; i++) {
        int bucket_index = arr[i] * num_buckets / (max_val + 1);
        int index = bucket_sizes[bucket_index];
        buckets[bucket_index][index] = arr[i];
        bucket_sizes[bucket_index]++;
    }

    // Ordenar cada bucket individualmente (utilizando otro algoritmo de clasificación)
    for (int i = 0; i < num_buckets; i++) {
        if (bucket_sizes[i] > 0) {
            int bucket_size = bucket_sizes[i];
            int* bucket = buckets[i];
            quicksort_medio(bucket, 0, bucket_size - 1);
        }
    }

    // Concatenar los elementos de los buckets en el arreglo original
    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        int bucket_size = bucket_sizes[i];
        if (bucket_size > 0) {
            int* bucket = buckets[i];
            for (int j = 0; j < bucket_size; j++) {
                arr[index] = bucket[j];
                index++;
            }
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucket_sizes);
}



// Algoritmo de Mezcla Directa o Natural
void mezcla_directa(int arr[], int inicio, int fin) {
    if (inicio < fin) {
        int medio = inicio + (fin - inicio) / 2;
        // Llamada recursiva para dividir la mitad izquierda
        mezcla_directa(arr, inicio, medio);

        // Llamada recursiva para dividir la mitad derecha
        mezcla_directa(arr, medio + 1, fin);

        // Mezcla de las dos mitades ordenadas
        int i, j, k;
        int n1 = medio - inicio + 1;
        int n2 = fin - medio;

        // Crear arreglos temporales para almacenar las mitades
        int *izquierda = malloc(n1 * sizeof(int));
        int *derecha = malloc(n2 * sizeof(int));

        // Copiar datos a los arreglos temporales
        for (i = 0; i < n1; i++) {
            izquierda[i] = arr[inicio + i];
        }
        for (j = 0; j < n2; j++) {
            derecha[j] = arr[medio + 1 + j];
        }

        // Mezclar los arreglos temporales en el arreglo original
        i = 0;  // Índice inicial del subarreglo izquierdo
        j = 0;  // Índice inicial del subarreglo derecho
        k = inicio;  // Índice inicial del subarreglo mezclado
        while (i < n1 && j < n2) {
            if (izquierda[i] <= derecha[j]) {
                arr[k] = izquierda[i];
                i++;
            } else {
                arr[k] = derecha[j];
                j++;
            }
            k++;
        }

        // Copiar los elementos restantes del subarreglo izquierdo
        while (i < n1) {
            arr[k] = izquierda[i];
            i++;
            k++;
        }

        // Copiar los elementos restantes del subarreglo derecho
        while (j < n2) {
            arr[k] = derecha[j];
            j++;
            k++;
        }

        free(izquierda);
        free(derecha);
    }
}

