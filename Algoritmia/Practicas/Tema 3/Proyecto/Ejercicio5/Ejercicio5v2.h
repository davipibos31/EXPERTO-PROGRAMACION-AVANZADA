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
