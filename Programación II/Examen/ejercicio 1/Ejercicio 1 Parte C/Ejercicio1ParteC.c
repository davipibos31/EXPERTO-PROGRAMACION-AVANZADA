#include <stdio.h>

int main() {
    int valores[100]; // array estático de tamaño 100
    int *puntero = valores; // puntero que apunta al inicio del array
    
    // Asignar valores al array
    for (int i = 0; i < 100; i++) {
        valores[i] = i + 1;
    }
    
    // Recorrer y mostrar los valores del array
    for (int i = 0; i < 100; i++) {
        printf("%d ", *puntero); // mostrar el valor al que apunta el puntero
        puntero++; // avanzar el puntero al siguiente elemento del array
    }
    
    return 0;
}
