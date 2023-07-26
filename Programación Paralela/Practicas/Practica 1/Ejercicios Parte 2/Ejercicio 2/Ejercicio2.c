#include <stdio.h>
#include <omp.h>

int main() {
    int i;

    // Static schedule
    printf("Static schedule:\n");
    #pragma omp parallel for schedule(static)
    for (i = 0; i < 10; i++) {
        printf("Thread %d, i = %d\n", omp_get_thread_num(), i);
    }

    // Dynamic schedule
    printf("\nDynamic schedule:\n");
    #pragma omp parallel for schedule(dynamic)
    for (i = 0; i < 10; i++) {
        printf("Thread %d, i = %d\n", omp_get_thread_num(), i);
    }

    // Guided schedule
    printf("\nGuided schedule:\n");
    #pragma omp parallel for schedule(guided)
    for (i = 0; i < 10; i++) {
        printf("Thread %d, i = %d\n", omp_get_thread_num(), i);
    }

    return 0;
}
