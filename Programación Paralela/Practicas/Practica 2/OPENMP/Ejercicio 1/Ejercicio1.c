#include <stdio.h>
#include <omp.h>

#define SIZE 10

void stencil_1d(float *y) {
    int i;
    #pragma omp parallel for
    for (i = 1; i < SIZE - 1; i++) {
        y[i] = (y[i-1] * y[i] * y[i+1]) / 3.0;
    }
}

int main() {
    float y[SIZE] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    
    printf("Original array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");
    
    stencil_1d(y);
    
    printf("Modified array:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");
    
    return 0;
}
