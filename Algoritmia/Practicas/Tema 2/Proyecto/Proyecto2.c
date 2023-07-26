#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACTORES 10
#define MAX_ATRIBUTOS 5
#define MAX_NOMBRE 100

typedef struct {
    char nombre[MAX_NOMBRE];
    char apellido[MAX_NOMBRE];
    int edad;
    char premioGoya;
    int cache;
} Actor;

void leerActores(Actor actores[MAX_ACTORES]) {
    FILE *archivo;
    char linea[MAX_NOMBRE * MAX_ATRIBUTOS];
    char *token;
    int i = 0;
    
    archivo = fopen("listaActores.csv", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    
    while (fgets(linea, sizeof(linea), archivo)) {
        token = strtok(linea, ";");
        strcpy(actores[i].apellido, token);
        
        token = strtok(NULL, ";");
        strcpy(actores[i].nombre, token);
        
        token = strtok(NULL, ";");
        actores[i].edad = atoi(token);
        
        token = strtok(NULL, ";");
        actores[i].premioGoya = token[0];
        
        token = strtok(NULL, ";");
        actores[i].cache = atoi(token);
            i++;
    }

    fclose(archivo);
}

int cumpleRangoEdad(int edad, int rangoEdadMin, int rangoEdadMax) {
    return (edad >= rangoEdadMin && edad <= rangoEdadMax);
}

int backtracking(Actor actores[MAX_ACTORES], Actor seleccionados[MAX_ACTORES], int numActoresSeleccionados, int numActoresRestantes, int rangoEdadMin, int rangoEdadMax, int goyaAcumulados, int cacheTotal, int *mejorCache, Actor *mejorCasting) {
    if (numActoresSeleccionados == numActoresRestantes) {
    if (cumpleRangoEdad(seleccionados[numActoresSeleccionados - 1].edad, rangoEdadMin, rangoEdadMax) && goyaAcumulados >= cacheTotal) {
    *mejorCache = cacheTotal;
    memcpy(mejorCasting, seleccionados, sizeof(Actor) * numActoresSeleccionados);
    return 1;
    }
    return 0;
    }

    int i;
    for (i = 0; i < MAX_ACTORES; i++) {
        if (actores[i].nombre[0] != '\0') {
            if (cumpleRangoEdad(actores[i].edad, rangoEdadMin, rangoEdadMax) && goyaAcumulados + actores[i].cache <= cacheTotal) {
                seleccionados[numActoresSeleccionados] = actores[i];
                if (backtracking(actores, seleccionados, numActoresSeleccionados + 1, numActoresRestantes, rangoEdadMin, rangoEdadMax, goyaAcumulados + (actores[i].premioGoya == 'S' ? 1 : 0), cacheTotal, mejorCache, mejorCasting)) {
                    return 1;
                }
                seleccionados[numActoresSeleccionados].nombre[0] = '\0'; // Deshacer la selección
            }
        }
    }

    return 0;
}

void mostrarCasting(Actor casting[MAX_ACTORES], int numActores) {
    printf("Casting:\n");
    int i;
    for (i = 0; i < numActores; i++) {
        printf("Actor %d: %s %s\n", i + 1, casting[i].nombre, casting[i].apellido);
        if (casting[i].premioGoya == 'S') {
        printf("Tiene premio Goya.\n");
        } else {
        printf("No tiene premio Goya.\n");
        }
    }
}

void mostrarResultado(Actor casting[MAX_ACTORES], int numActores, int cacheTotal) {
    printf("\n*** Resultado ***\n");
    if (numActores > 0) {
        mostrarCasting(casting, numActores);
        printf("Coste total del casting: %d\n", cacheTotal);
    } else {
        printf("No hay solución que cumpla con las condiciones.\n");
    }
}

int main() {
    Actor actores[MAX_ACTORES];
    Actor seleccionados[MAX_ACTORES];
    int numActores;
    int rangoEdadMin, rangoEdadMax;
    int cacheTotal;
    int mejorCache = -1;
    Actor mejorCasting[MAX_ACTORES];
    leerActores(actores);

    printf("Ingrese el número de actores en el casting: ");
    scanf("%d", &numActores);

    printf("Ingrese el rango de edad mínimo: ");
    scanf("%d", &rangoEdadMin);

    printf("Ingrese el rango de edad máximo: ");
    scanf("%d", &rangoEdadMax);

    printf("Ingrese la cantidad total de premios Goya: ");
    scanf("%d", &cacheTotal);

    backtracking(actores, seleccionados, 0, numActores, rangoEdadMin, rangoEdadMax, 0, cacheTotal, &mejorCache, mejorCasting);

    mostrarResultado(mejorCasting, numActores, mejorCache);

    return 0;
}