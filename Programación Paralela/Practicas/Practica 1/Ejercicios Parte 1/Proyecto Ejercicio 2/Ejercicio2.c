#include <stdio.h>
#include <omp.h>

int main() {
    int i;
    int n = 10;
    int suma = 0;

    #pragma omp parallel for firstprivate(n) lastprivate(i) reduction(+:suma)
    for (i = 0; i < n; i++) {
        suma += i;
        printf("Hilo %d: i = %d, suma = %d\n", omp_get_thread_num(), i, suma);
    }

    printf("Valor final de i fuera del parallel for: %d\n", i);
    printf("Valor final de suma fuera del parallel for: %d\n", suma);

    return 0;
}
