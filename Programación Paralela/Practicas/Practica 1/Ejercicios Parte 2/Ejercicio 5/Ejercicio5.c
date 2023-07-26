#include <stdio.h>
#include <omp.h>

#define N 1000

void multiplicar_matriz_vector_secuencial(double matriz[N][N], double vector[N], double resultado[N]) {
    for (int i = 0; i < N; i++) {
        resultado[i] = 0.0;
        for (int j = 0; j < N; j++) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }
}

void multiplicar_matriz_vector_paralelo(double matriz[N][N], double vector[N], double resultado[N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        resultado[i] = 0.0;
        for (int j = 0; j < N; j++) {
            resultado[i] += matriz[i][j] * vector[j];
        }
    }
}

int main() {
    double matriz[N][N];
    double vector[N];
    double resultado[N];

    // Inicializar la matriz y el vector

    double timeIni, timeFin;

    // Versión secuencial
    timeIni = omp_get_wtime();
    multiplicar_matriz_vector_secuencial(matriz, vector, resultado);
    timeFin = omp_get_wtime();
    printf("Tiempo secuencial = %f segundos\n", timeFin - timeIni);

    // Versión paralela
    timeIni = omp_get_wtime();
    multiplicar_matriz_vector_paralelo(matriz, vector, resultado);
    timeFin = omp_get_wtime();
    printf("Tiempo paralelo = %f segundos\n", timeFin - timeIni);

    return 0;
}
