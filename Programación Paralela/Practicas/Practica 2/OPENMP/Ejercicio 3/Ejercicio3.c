#include <stdio.h>
#include <omp.h>

#define SIZE 10

int reduction_sum(int *array) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }
    return sum;
}

int main() {
    int array[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    printf("Array elements:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    int sum = reduction_sum(array);
    
    printf("Sum: %d\n", sum);
    
    return 0;
}
