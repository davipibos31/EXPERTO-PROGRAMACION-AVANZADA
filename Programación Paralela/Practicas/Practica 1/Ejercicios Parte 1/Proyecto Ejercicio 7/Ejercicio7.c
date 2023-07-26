#include <stdio.h>
#include <omp.h>

static long num_steps = 100000;
double step;

int main() {
    int num_threads[] = {2, 4, 6, 8};
    double pi, sum = 0.0;
    double start_time, end_time;

    step = 1.0 / (double)num_steps;

    printf("Número de pasos: %ld\n", num_steps);

    for (int k = 0; k < sizeof(num_threads) / sizeof(num_threads[0]); k++) {
        int num_procs = num_threads[k];

        omp_set_num_threads(num_procs);

        sum = 0.0;
        start_time = omp_get_wtime();

        #pragma omp parallel for reduction(+:sum)
        for (int i = 1; i <= num_steps; i++) {
            double x = (i - 0.5) * step;
            sum = sum + 4.0 / (1.0 + x * x);
        }

        pi = step * sum;

        end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;

        printf("Número de hilos: %d, Pi = %f, Tiempo de ejecución: %f segundos\n", num_procs, pi, elapsed_time);
    }

    return 0;
}
