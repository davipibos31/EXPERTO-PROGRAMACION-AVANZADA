#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Función de búsqueda directa
void busquedaDirecta(char *texto, char *patron) {
    int reinicios = 0;
    int texto_len = strlen(texto);
    int patron_len = strlen(patron);

    for (int i = 0; i <= texto_len - patron_len; i++) {
        int j;
        for (j = 0; j < patron_len; j++) {
            if (texto[i + j] != patron[j])
                break;
        }

        if (j == patron_len) {
            printf("Coincidencia encontrada en la posición %d\n", i);
        }
        else {
            reinicios++;
        }
    }

    printf("Número total de reinicios: %d\n", reinicios);
}

// Implementación de KMP
void calcularLPS(char *patron, int *lps) {
    int len = 0;
    int i = 1;
    int m = strlen(patron);

    lps[0] = 0;

    while (i < m) {
        if (patron[i] == patron[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
// Función de búsqueda KMP
void busquedaKMP(char *texto, char *patron) {
     int n = strlen(texto);
    int m = strlen(patron);
    int *lps = (int *)malloc(sizeof(int) * m);
    int i = 0;
    int j = 0;

    calcularLPS(patron, lps);

    while (i < n) {
        if (patron[j] == texto[i]) {
            j++;
            i++;
        }

        if (j == m) {
            printf("Coincidencia encontrada en la posición %d\n", i - j);
            j = lps[j - 1];
        }
        else if (i < n && patron[j] != texto[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    free(lps);

    printf("Tiempo de ejecución y número de reinicios de KMP\n");
}


// Implementación de BM
#define MAX_CHAR 256

int maxx(int a, int b) {
    return (a > b) ? a : b;
}

void preprocesarBC(char *patron, int m, int *bc) {
    for (int i = 0; i < MAX_CHAR; i++) {
        bc[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        bc[(int)patron[i]] = i;
    }
}

void busquedaBM(char *texto, char *patron) {
    int n = strlen(texto);
    int m = strlen(patron);
    int *bc = (int *)malloc(sizeof(int) * MAX_CHAR);
    int s = 0;

    preprocesarBC(patron, m, bc);

    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && patron[j] == texto[s + j]) {
            j--;
        }

        if (j < 0) {
            printf("Coincidencia encontrada en la posición %d\n", s);
            s += (s + m < n) ? m - bc[texto[s + m]] : 1;
        }
        else {
            s += maxx(1, j - bc[texto[s + j]]);
        }
    }

    free(bc);

    printf("Tiempo de ejecución y número de reinicios de BM\n");
}

int main() {
    char texto[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    char patron[] = "sit";

    clock_t start, end;
    double tiempo;

    printf("Texto: %s\n", texto);
    printf("Patrón: %s\n", patron);

    // Búsqueda directa
    start = clock();
    busquedaDirecta(texto, patron);
    end = clock();
    tiempo = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución de búsqueda directa: %.6f segundos\n", tiempo);

    // Búsqueda KMP
    start = clock();
    busquedaKMP(texto, patron);
    end = clock();
    tiempo = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución de KMP: %.6f segundos\n", tiempo);

    // Búsqueda BM
    start = clock();
    busquedaBM(texto, patron);
    end = clock();
    tiempo = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución de BM: %.6f segundos\n", tiempo);

    return 0;
}

