#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 5500;
    float f = 1.34;

    // ESCRIBIENDO DATOS

    FILE * file;

    file=fopen("fichero.txt", "w");

    fputs("en un lugar de la mancha\n",file);
    fputs("de cuyo nombre\n",file);
    fputs("no quiero acordarme...\n",file);

    fputc('S',file);
    fputc('T',file);
    fputc('A',file);
    fputc('R',file);
    fputc(' ',file);
    fputc('W',file);
    fputc('A',file);
    fputc('R',file);
    fputc('S',file);
    fputc('\n',file);

    fprintf(file,"a=%d f=%.3f",a,f);

    fclose(file);

    //rename("fichero.txt", "otro.txt");

    //remove("otro.txt");

    // LEYENDO DATOS
    char cadena[50];
    char c;

    file=fopen("fichero.txt", "r");

    fscanf(file,"%s",cadena);
    printf("Primera llamada scanf: <%s> \n",cadena);

    fscanf(file,"%s",cadena);
    printf("Segunda llamada a scanf: <%s> \n",cadena);

    fgets(cadena,50,file);
    printf("Primera llamada a gets: <%s> \n",cadena);

    fgets(cadena,50,file);
    printf("Segunda llamada a gets: <%s> \n",cadena);

    c=fgetc(file);
    printf("Primera llamada a fgetc: <%c> \n",c);

    c=fgetc(file);
    printf("Segunda llamada a fgetc: <%c> \n",c);

    fclose(file);

    // Leyendo el fichero completo: usando fgets

    file=fopen("fichero.txt", "r");
    printf("\n\nLeyendo el fichero usando fgets:\n");
    while(fgets(cadena,50,file) != NULL ) {
        printf("%s", cadena);
    }
    fclose(file);

    // Leyendo el fichero completo: usando fgetc

    file=fopen("fichero.txt", "r");
    printf("\n\nLeyendo el fichero usando fgetc:\n");
    while( (c=fgetc(file)) != EOF ) {
        printf("%c--", c);
    }
    fclose(file);


    // Leyendo el fichero completo: usando fscanf

    file=fopen("fichero.txt", "r");
    printf("\n\nLeyendo el fichero usando fscanf:\n");
    while(fscanf(file,"%s",cadena) >0 ) {
        printf("%s--", cadena);
    }
    fclose(file);

   // printf("Ultima linea leida del fichero: <%s> \n", cadena);


    fclose(file);



    return 0;
}