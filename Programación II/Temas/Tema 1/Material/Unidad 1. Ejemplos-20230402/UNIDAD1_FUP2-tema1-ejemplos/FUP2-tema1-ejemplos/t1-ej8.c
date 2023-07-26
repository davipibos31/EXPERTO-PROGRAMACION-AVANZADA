#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 2

typedef struct Punto {
    float x;
    float y;
} Punto_t;

int main(void)
{

    int i;
    Punto_t vp[TAM],aux[TAM];
    FILE * fp;

    // Inicializamos los 5 puntos

    printf("Introduzca %d puntos en el plano (x,y) \n",TAM);
    for (i=0;i<TAM;i++) {
        printf("\tIntroduzca valor punto %d: ",i);
        scanf("%f,%f",&vp[i].x,&vp[i].y);
    }

    // Escribimos los valores en fichero
    fp = fopen("puntos.db","wb");
    fwrite(vp,sizeof(Punto_t),TAM,fp);
    fclose(fp);

    // Abrimos de nuevo el fichero y leemos la estructura almacenada
    fp = fopen("puntos.db","r");
    fread(aux,sizeof(Punto_t),TAM,fp);
    fclose(fp);

    // Imprimos por pantalla
    printf("\n\nImprimos los puntos leídos del fichero 'puntos.db'\n");
    for (i=0; i<TAM;i++)
        printf("\tPunto %d = (%f,%f)\n",i, aux[i].x, aux[i].y);

    return (EXIT_SUCCESS);
}
