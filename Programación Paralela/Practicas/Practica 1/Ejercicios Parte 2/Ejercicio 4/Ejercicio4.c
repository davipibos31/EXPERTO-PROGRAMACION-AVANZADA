#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int vector[N];
    // Inicializar el vector

    int max_value = vector[0];
    int min_value = vector[0];

    #pragma omp parallel for reduction(max:max_value) reduction(min:min_value)
    for (int i = 0; i < N; i++) {
        if (vector[i] > max_value) {
            max_value = vector[i];
        }
        if (vector[i] < min_value) {
            min_value = vector[i];
        }
    }

    printf("Máximo valor: %d\n", max_value);
    printf("Mínimo valor: %d\n", min_value);

    return 0;
}
