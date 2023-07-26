#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM 100

bool es_primo(int n) {

    int i;
    for (i=2; i<n; i++)
        if (n%i == 0)
            return false;
    return true;

}

int main(void)
{

    FILE * fichero;
    int i, n;
    int primos[NUM];

    // Generamos y almacenamos en el fichero los 1000 primeros numeros primos
    fichero = fopen("primos.txt", "w");
    i=1; n=0;
    while(n<NUM) {
        if(es_primo(i)) {
            fprintf(fichero,"%d\n",i);
            n++;
        }
        i++;
    }
    fclose(fichero);

    // Ahora leemos del fichero los primos y los almacenamos en un array
    fichero = fopen("primos.txt", "r");
    i=0;

    while(fscanf(fichero, "%d", &n) != EOF){
        primos[i]=n;
        i++;
    }
    fclose(fichero);

    // Imprimos el array
    fprintf(stdout, "Imprimos los primos almacenados en el array...\n");
    for (i=0;i<NUM;i++) {
        fprintf(stdout,"%d-",primos[i]);
    }

    return (EXIT_SUCCESS);
}
