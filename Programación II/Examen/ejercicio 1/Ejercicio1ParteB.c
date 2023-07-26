#include <stdio.h>
#include <stdlib.h>

int main() {
    int num_filas, num_columnas;
    float **matriz;

    // Obtener el tamaño de la matriz del usuario
    printf("Ingrese el número de filas de la matriz: ");
    scanf("%d", &num_filas);
    printf("Ingrese el número de columnas de la matriz: ");
    scanf("%d", &num_columnas);

    // Crear la matriz dinámica
    matriz = (float **)malloc(num_filas * sizeof(float *));
    for (int i = 0; i < num_filas; i++) {
        matriz[i] = (float *)malloc(num_columnas * sizeof(float));
    }

    // Leer los valores de la matriz del usuario
    for (int i = 0; i < num_filas; i++) {
        for (int j = 0; j < num_columnas; j++) {
            printf("Ingrese el valor para la posición (%d, %d): ", i, j);
            scanf("%f", &matriz[i][j]);
        }
    }

    // Imprimir la matriz
    printf("La matriz ingresada es:\n");
    for (int i = 0; i < num_filas; i++) {
        for (int j = 0; j < num_columnas; j++) {
            printf("%.2f ", matriz[i][j]);
        }
        printf("\n");
    }

    // Liberar la memoria utilizada por la matriz
    for (int i = 0; i < num_filas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
