#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * fuente, * destino;
    int ch;

    if ((fuente = fopen("fichero1.txt","r"))==NULL) {
        fprintf(stderr,"No se puede abrir el fichero fuente \n");
        exit(EXIT_FAILURE); // También return -1;
    }
    if ((destino = fopen("fichero2.txt","w"))==NULL) {
        fprintf(stderr,"No se puede abrir el fichero destino \n");
        fclose(fuente);
        exit(EXIT_FAILURE); // También return -1;
    }

    printf("Procediendo a realizar copia...");

    while ((ch = fgetc(fuente)) != EOF)
        fputc(ch,destino);

    printf("Copia completada!");

    fclose(fuente);
    fclose(destino);

    return 0;
}
