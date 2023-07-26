#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIUDADES 100
#define MAX_NOMBRE_CIUDAD 50
#define INFINITO 999999

typedef struct {
    char nombre[MAX_NOMBRE_CIUDAD];
    int distancia;
} Conexion;

typedef struct {
    char nombre[MAX_NOMBRE_CIUDAD];
    Conexion conexiones[MAX_CIUDADES];
    int num_conexiones;
} Ciudad;

Ciudad ciudades[MAX_CIUDADES];
int num_ciudades;

void cargarInformacion() {
    FILE *fichero;
    char linea[100];
    char *token;
    int i = 0;

    fichero = fopen("carreteras.txt", "r");
    if (fichero == NULL) {
        printf("Error al abrir el fichero.\n");
        exit(1);
    }

    while (fgets(linea, sizeof(linea), fichero)) {
        if (linea[0] == '#') {
            // Ignorar comentarios
            continue;
        }

        token = strtok(linea, " \n");
        if (token != NULL) {
            strcpy(ciudades[i].nombre, token);
            ciudades[i].num_conexiones = 0;

            token = strtok(NULL, " \n");
            while (token != NULL) {
                strcpy(ciudades[i].conexiones[ciudades[i].num_conexiones].nombre, token);

                token = strtok(NULL, " \n");
                ciudades[i].conexiones[ciudades[i].num_conexiones].distancia = atoi(token);

                token = strtok(NULL, " \n");
                ciudades[i].num_conexiones++;
            }

            i++;
        }
    }

    num_ciudades = i;

    fclose(fichero);
}

int encontrarCiudad(char *nombre) {
    int i;

    for (i = 0; i < num_ciudades; i++) {
        if (strcmp(ciudades[i].nombre, nombre) == 0) {
            return i;
        }
    }

    return -1;
}

void comprobarFichero() {
    int i, j;
    int visitado[MAX_CIUDADES];
    int alcanzables[MAX_CIUDADES];
    int cola[MAX_CIUDADES];
    int inicio, fin;

    // Inicializar arrays de visitados y alcanzables
    for (i = 0; i < num_ciudades; i++) {
        visitado[i] = 0;
        alcanzables[i] = 0;
    }

    // Marcar la primera ciudad como alcanzable
    alcanzables[0] = 1;

    inicio = 0;
    fin = 1;
    cola[0] = 0;

    // Recorrer las ciudades mediante BFS
    while (inicio < fin) {
        int ciudad_actual = cola[inicio];
        visitado[ciudad_actual] = 1;
        inicio++;

        for (j = 0; j < ciudades[ciudad_actual].num_conexiones; j++) {
            int ciudad_conexion = encontrarCiudad(ciudades[ciudad_actual].conexiones[j].nombre);
            if (ciudad_conexion != -1 && !visitado[ciudad_conexion]) {
                alcanzables[ciudad_conexion] = 1;
                cola[fin] = ciudad_conexion;
                fin++;
            }
        }
    }

    // Comprobar si hay ciudades aisladas o inalcanzables
    for (i = 0; i < num_ciudades; i++) {
        if (!alcanzables[i]) {
            printf("La ciudad %s es inalcanzable desde otra ciudad.\n", ciudades[i].nombre);
        }
    }

    for (i = 0; i < num_ciudades; i++) {
        if (!visitado[i]) {
            printf("La ciudad %s es una ciudad aislada.\n", ciudades[i].nombre);
        }
    }

    if (inicio == num_ciudades) {
        printf("El fichero es válido. No existen ciudades aisladas ni inalcanzables.\n");
    }
}

void dijkstra(int origen, int destino) {
    int distancias[MAX_CIUDADES];
    int visitado[MAX_CIUDADES];
    int anterior[MAX_CIUDADES];
    int i, j;
    int min, min_idx;

    // Inicializar distancias y visitados
    for (i = 0; i < num_ciudades; i++) {
        distancias[i] = INFINITO;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    distancias[origen] = 0;

    for (i = 0; i < num_ciudades; i++) {
        min = INFINITO;
        min_idx = -1;

        // Encontrar el nodo no visitado con distancia mínima
        for (j = 0; j < num_ciudades; j++) {
            if (!visitado[j] && distancias[j] < min) {
                min = distancias[j];
                min_idx = j;
            }
        }

        if (min_idx == -1) {
            break; // No hay más nodos alcanzables
        }

        visitado[min_idx] = 1;

        // Actualizar distancias de los nodos adyacentes
        for (j = 0; j < ciudades[min_idx].num_conexiones; j++) {
            int ciudad_conexion = encontrarCiudad(ciudades[min_idx].conexiones[j].nombre);
            if (ciudad_conexion != -1 && !visitado[ciudad_conexion]) {
                int nueva_distancia = distancias[min_idx] + ciudades[min_idx].conexiones[j].distancia;
                if (nueva_distancia < distancias[ciudad_conexion]) {
                    distancias[ciudad_conexion] = nueva_distancia;
                    anterior[ciudad_conexion] = min_idx;
                }
            }
        }
    }

    // Mostrar la ruta más corta
    if (distancias[destino] == INFINITO) {
        printf("No existe ruta entre las ciudades especificadas.\n");
    } else {
        printf("Ruta más corta: %s", ciudades[destino].nombre);
        int ciudad_actual = destino;
        while (anterior[ciudad_actual] != -1) {
            ciudad_actual = anterior[ciudad_actual];
            printf(" <- %s", ciudades[ciudad_actual].nombre);
        }
        printf("\nDistancia total: %d km\n", distancias[destino]);
    }
}

int main() {
    int opcion;
    char ciudad_origen[MAX_NOMBRE_CIUDAD];
    char ciudad_destino[MAX_NOMBRE_CIUDAD];

    cargarInformacion();

    do {
        printf("\n--- Menú ---\n");
        printf("1. Comprobar validez del fichero\n");
        printf("2. Obtener ruta más corta\n");
        printf("3. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                comprobarFichero();
                break;
            case 2:
                printf("Ingrese la ciudad de origen: ");
                scanf("%s", ciudad_origen);
                printf("Ingrese la ciudad de destino: ");
                scanf("%s", ciudad_destino);
                dijkstra(encontrarCiudad(ciudad_origen), encontrarCiudad(ciudad_destino));
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }
    } while (opcion != 3);

    return 0;
}
