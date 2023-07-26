#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    FILE *fuente, *destino;
    int ch;

    if ((fuente = fopen("fichero1.bin", "rb")) == NULL) {
        fprintf(stderr, "No se puede abrir el fichero fuente \n");
        exit (EXIT_FAILURE);
    }

    if ((destino = fopen("fichero2.bin", "wb")) == NULL) {
        fprintf(stderr, "No se puede abrir el fichero destino %s\n");
        fclose(fuente);
        exit (EXIT_FAILURE);
    }

    while (fread(&ch, sizeof (ch), 1, fuente) > 0)
        fwrite(&ch, sizeof (ch), 1, destino);

    fclose(fuente);
    fclose(destino);

    return (EXIT_SUCCESS);

}
