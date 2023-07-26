#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[50];
    char telefono[15];
} Contacto;

typedef struct Nodo {
    Contacto contacto;
    struct Nodo* izquierda;
    struct Nodo* derecha;
} Nodo;

Nodo* crearNodo(Contacto contacto) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevoNodo->contacto.nombre, contacto.nombre);
    strcpy(nuevoNodo->contacto.telefono, contacto.telefono);
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

Nodo* insertarContacto(Nodo* raiz, Contacto contacto) {
    if (raiz == NULL) {
        return crearNodo(contacto);
    }
    
    if (strcmp(contacto.nombre, raiz->contacto.nombre) < 0) {
        raiz->izquierda = insertarContacto(raiz->izquierda, contacto);
    }
    else if (strcmp(contacto.nombre, raiz->contacto.nombre) > 0) {
        raiz->derecha = insertarContacto(raiz->derecha, contacto);
    }
    
    return raiz;
}

char* buscarContacto(Nodo* raiz, char* nombre) {
    if (raiz == NULL || strcmp(nombre, raiz->contacto.nombre) == 0) {
        return raiz != NULL ? raiz->contacto.telefono : NULL;
    }
    
    if (strcmp(nombre, raiz->contacto.nombre) < 0) {
        return buscarContacto(raiz->izquierda, nombre);
    }
    else {
        return buscarContacto(raiz->derecha, nombre);
    }
}

void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}

void mostrarMenu() {
    printf("\nAgenda Telefónica\n");
    printf("-----------------\n");
    printf("1. Insertar contacto\n");
    printf("2. Buscar contacto\n");
    printf("3. Salir\n");
    printf("Ingrese el número de la opción: ");
}

int main() {
    Nodo* raiz = NULL;
    Contacto nuevoContacto;
    int opcion;
    char nombreBusqueda[50];
    
    do {
        mostrarMenu();
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del contacto: ");
                scanf("%s", nuevoContacto.nombre);
                printf("Ingrese el número de teléfono: ");
                scanf("%s", nuevoContacto.telefono);
                raiz = insertarContacto(raiz, nuevoContacto);
                printf("Contacto insertado correctamente.\n");
                break;
                
            case 2:
                printf("Ingrese el nombre del contacto a buscar: ");
                scanf("%s", nombreBusqueda);
                char* telefono = buscarContacto(raiz, nombreBusqueda);
                if (telefono != NULL) {
                    printf("El número de teléfono de %s es: %s\n", nombreBusqueda, telefono);
                }
                else {
                    printf("Contacto no encontrado.\n");
                }
                break;
            case 3:
                printf("Saliendo de la agenda telefónica...\n");
                break;
                
            default:
                printf("Opción inválida. Por favor, ingrese un número válido.\n");
                break;
        }
        
    } while (opcion != 3);
    
    liberarArbol(raiz);
    
    return 0;
}
