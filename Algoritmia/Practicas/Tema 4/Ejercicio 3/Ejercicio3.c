#include <stdio.h>

int contarPalabrasArchivo(const char* archivo) {
    FILE* f = fopen(archivo, "r");
    if (f == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return -1;
    }

    int contador = 0;
    int caracterAnterior = ' ';
    int caracterActual;

    while ((caracterActual = fgetc(f)) != EOF) {
        if (caracterActual == ' ' || caracterActual == '\n' || caracterActual == '\t') {
            if (caracterAnterior != ' ' && caracterAnterior != '\n' && caracterAnterior != '\t') {
                contador++;
            }
        }
        caracterAnterior = caracterActual;
    }

    fclose(f);
    return contador;
}

int main() {
    const char* nombreArchivo = "textobusq.txt";
    int cantidadPalabras = contarPalabrasArchivo(nombreArchivo);
    printf("La cantidad de palabras en el archivo %s es: %d\n", nombreArchivo, cantidadPalabras);

    return 0;
}
