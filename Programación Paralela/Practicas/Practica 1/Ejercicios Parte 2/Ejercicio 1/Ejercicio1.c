#include <stdio.h>
#include <omp.h>

void tarea_uno() {
    // Código de la tarea uno
}

void tarea_dos() {
    // Código de la tarea dos
}

int main() {
    double timeIni, timeFin;
    timeIni = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            double timeSection1 = omp_get_wtime();
            tarea_uno();
            double timeSection1End = omp_get_wtime();
            printf("Tiempo total de la sección 1 = %f segundos\n", timeSection1End - timeSection1);
        }

        #pragma omp section
        {
            double timeSection2 = omp_get_wtime();
            tarea_dos();
            double timeSection2End = omp_get_wtime();
            printf("Tiempo total de la sección 2 = %f segundos\n", timeSection2End - timeSection2);
        }
    }

    timeFin = omp_get_wtime();
    printf("Tiempo total = %f segundos\n", timeFin - timeIni);

    return 0;
}
