#include <stdio.h>
#include <stdlib.h>

#define MAX_NODOS 100
#define MAX_COLORES 5

int grafo[MAX_NODOS][MAX_NODOS];
int nodos;
int colores[MAX_NODOS];

// Función para verificar si un nodo se puede colorear con un color específico
int esSeguro(int nodo, int color) {
    for (int i = 0; i < nodos; i++) {
        if (grafo[nodo][i] && colores[i] == color) {
            return 0;
        }
    }
    return 1;
}

// Función de backtracking para encontrar la solución
int colorearGrafo(int m, int nodo) {
    if (nodo == nodos) {
        return 1; // Se ha coloreado todos los nodos
    }

    for (int i = 0; i < m; i++) {
        if (esSeguro(nodo, i)) {
            colores[nodo] = i;

            if (colorearGrafo(m, nodo + 1)) {
                return 1;
            }

            colores[nodo] = -1; // Retroceder
        }
    }

    return 0;
}

int main() {
    char nombreArchivo[100];
    int m;

    printf("Ingrese la ruta del archivo de grafo: ");
    scanf("%s", nombreArchivo);

    printf("Ingrese el número de colores (maximo 5): ");
    scanf("%d", &m);

    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    fscanf(archivo, "%d", &nodos);

    for (int i = 0; i < nodos; i++) {
        for (int j = 0; j < nodos; j++) {
            fscanf(archivo, "%d", &grafo[i][j]);
        }
    }

    fclose(archivo);

    for (int i = 0; i < nodos; i++) {
        colores[i] = -1; // -1 indica que el nodo no ha sido coloreado aún
    }

    if (colorearGrafo(m, 0)) {
        printf("Solución encontrada:\n");
        for (int i = 0; i < nodos; i++) {
            printf("Nodo %d: Color %d\n", i, colores[i]);
        }
    } else {
        printf("No existe solución.\n");
    }

    return 0;
}
