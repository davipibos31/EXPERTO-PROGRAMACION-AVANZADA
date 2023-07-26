#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE * destino;
    int ch;

    if((destino=fopen("salida.txt", "w"))==NULL) {
        fprintf(stderr, "No se puede abrir el fichero \n");
        exit(EXIT_FAILURE);
    }

    fputs("Estamos creando un fichero de texto...\n", destino);
    fputs("con este contenido \n", destino);
    fprintf(destino, "%d + %d = %d \n", 3, 4, 7);
    fputs("Aqui terminamos. \n", destino);
    fclose(destino);

    return (EXIT_SUCCESS);
}
