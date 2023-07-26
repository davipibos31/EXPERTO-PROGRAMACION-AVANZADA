#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void)
{

    FILE * fp;
    int i,n;
    int v1[10], v2[10];

    ////// OPCIÓN 1 /////

    // Escribimos 10 enteros en fichero
    fp = fopen("enteros1.dat", "wb");
    for (i=0;i<10;i++)
        fwrite(&i, sizeof(int), 1, fp);
    fclose(fp);

    // Leemos

    fp = fopen("enteros1.dat", "r");
    printf("Imprimiendo valores leidos del fichero enteros1.dat: ");
    for(i=0;i<10;i++) {
        fread(&n, sizeof(int),1,fp);
        printf("%d \n",n);
    }
    fclose(fp);

    ////// OPCIÓN 2 /////

    // Escribimos
    fp = fopen("enteros2.dat", "wb");
    for(i=0;i<10; i++)
        v1[i]=2*i;
    fwrite(v1,sizeof(int),10,fp);
    fclose(fp);

    // Leemos
    fp = fopen("enteros2.dat", "r");
    fread(v2,sizeof(int),10,fp);
    printf("Imprimiendo valores leidos del fichero enteros2.dat: ");
    for(i=0;i<10;i++)
        printf("%d ",v2[i]);
    fclose(fp);

    return (EXIT_SUCCESS);
}
