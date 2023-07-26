#include <stdio.h>
#include <omp.h>

#define N 10

void saxpy(float *x, float *y, float alpha) {
    int i;
    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        y[i] = alpha * x[i] + y[i];
    }
}

int main() {
    float x[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float y[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    float alpha = 2.0;
    
    printf("Original array y:\n");
    for (int i = 0; i < N; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");
    
    saxpy(x, y, alpha);
    
    printf("Modified array y:\n");
    for (int i = 0; i < N; i++) {
        printf("%.2f ", y[i]);
    }
    printf("\n");
    
    return 0;
}
