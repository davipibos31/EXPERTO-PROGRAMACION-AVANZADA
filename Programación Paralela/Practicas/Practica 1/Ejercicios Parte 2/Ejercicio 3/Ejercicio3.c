#include <stdio.h>
#include <omp.h>

#define N 5000

double producto_escalar_secuencial(double *a, double *b) {
    double total = 0.0;
    for (int i = 0; i < N; i++) {
        total += a[i] * b[i];
    }
    return total;
}

double producto_escalar_paralelo_reduction(double *a, double *b) {
    double total = 0.0;
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < N; i++) {
        total += a[i] * b[i];
    }
    return total;
}

double producto_escalar_paralelo_critical(double *a, double *b) {
    double total = 0.0;
    #pragma omp parallel
    {
        double local_total = 0.0;
        #pragma omp for
        for (int i = 0; i < N; i++) {
            local_total += a[i] * b[i];
        }
        #pragma omp critical
        total += local_total;
    }
    return total;
}

int main() {
    double a[N], b[N];
    // Inicializar los vectores a y b

    double timeIni, timeFin;

    // Versión secuencial
    timeIni = omp_get_wtime();
    double resultado_secuencial = producto_escalar_secuencial(a, b);
    timeFin = omp_get_wtime();
    printf("Tiempo secuencial = %f segundos\n", timeFin - timeIni);

    // Versión paralela con reduction
    for (int num_hilos = 1; num_hilos <= 8; num_hilos++) {
        omp_set_num_threads(num_hilos);
        timeIni = omp_get_wtime();
        double resultado_paralelo_reduction = producto_escalar_paralelo_reduction(a, b);
        timeFin = omp_get_wtime();
        printf("Tiempo paralelo (reduction) con %d hilos = %f segundos\n", num_hilos, timeFin - timeIni);
        printf("Resultado paralelo (reduction) = %f\n", resultado_paralelo_reduction);
    }

    // Versión paralela con critical
    for (int num_hilos = 1; num_hilos <= 8; num_hilos++) {
        omp_set_num_threads(num_hilos);
        timeIni = omp_get_wtime();
        double resultado_paralelo_critical = producto_escalar_paralelo_critical(a, b);
        timeFin = omp_get_wtime();
        printf("Tiempo paralelo (critical) con %d hilos = %f segundos\n", num_hilos, timeFin - timeIni);
        printf("Resultado paralelo (critical) = %f\n", resultado_paralelo_critical);
    }

    return 0;
}
