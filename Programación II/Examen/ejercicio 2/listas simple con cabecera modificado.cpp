#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

struct nodo {
    int dni;
    char apellidos[50];
    struct nodo *psig;
};

typedef struct nodo *Lista;
typedef struct nodo *Posicion;

struct nodo* l_int_crear(void) {
    struct nodo *paux;  // Crea el nodo cabecera
    paux = (struct nodo *) malloc(sizeof(struct nodo));
    
    if (paux != NULL) {
        paux->psig = NULL;
    }
    
    return (paux);
}

struct nodo* l_int_insertar(struct nodo *l, struct nodo *pindice, int dni, char apellidos[50]) {
    struct nodo *paux;
    paux = (struct nodo *) malloc(sizeof(struct nodo));
    
    if (paux != NULL) {
        paux->dni = dni;
        strcpy(paux->apellidos, apellidos);
        paux->psig = pindice->psig;
        pindice->psig = paux;
    }
    
    return (paux);
}

struct nodo* l_int_primero(struct nodo *l) {
    return (l);  // Devuelve un puntero al nodo cabecera
}

struct nodo* l_int_ultimo(struct nodo *l) {
    struct nodo *paux;  // El último elemento de la lista es NULL
    paux = l;
    
    while (paux->psig != NULL)
        paux = paux->psig;
    
    return (paux);
}

struct nodo* l_int_siguiente(struct nodo *l, struct nodo *pindice) {
    return (pindice->psig);
}

struct nodo* l_int_anterior(struct nodo *l, struct nodo *pindice) {
    struct nodo *paux;
    paux = l;
    
    while (paux->psig != pindice)
        paux = paux->psig;
    
    return (paux);
}

int l_int_longitud(struct nodo *l) {
    int contador = 0;
    struct nodo *paux;
    paux = l;
    
    while (paux->psig != NULL) {
        contador++;
        paux = paux->psig;
    }
    
    return (contador);
}

struct nodo* l_int_localizar(struct nodo *l, const int posicion) {
    struct nodo *paux;
    int c;
    paux = l;
    c = posicion;
    
    while ((c > 0) && (paux->psig != NULL)) {
        paux = paux->psig;
        c--;
    }
    
    if (c != 0)
        paux = NULL;
    
    return (paux);
}

int l_int_elemento(struct nodo *l, struct nodo *pindice) {
    return (pindice->dni);
}

void l_int_borrar(struct nodo *l, struct nodo *pindice) {
    struct nodo *paux;
    paux = l_int_anterior(l, pindice);
    paux->psig = pindice->psig;
    free(pindice);
}

void l_int_destruir(struct nodo *l) {
    struct nodo *pborra;
    struct nodo *paux;
    paux = l;
    
    do {
        pborra = paux;
        paux = paux->psig;
        free(pborra);
    } while (paux != NULL);
}

int main(int argc, char** argv) {
    Lista a;
    Posicion c1;
    int dni;
    char apellidos[50];
    int conta;
    
    a = l_int_crear();
    
    if (a == NULL) {
        perror("Error al crear la lista");
        exit(-1);
    }
    
    c1 = l_int_primero(a);
    
    printf("Insertando los números (del 0 al 20):\n");
    
    for (conta = 0; conta <= 20; conta++) {
        printf("DNI: ");
        scanf("%d", &dni);
        printf("Apellidos: ");
        scanf("%s", apellidos);
        l_int_insertar(a, c1, dni, apellidos);
        c1 = l_int_siguiente(a, c1);
    }
    
    printf("\n");
    
    printf("La lista contiene %d números\n", l_int_longitud(a));
    
    printf("Lista en orden:\n");
    
    c1 = l_int_primero(a);
    
    for (conta = 0; conta < l_int_longitud(a); conta++) {
        c1 = l_int_siguiente(a, c1);
        printf("DNI: %d, Apellidos: %s\n", l_int_elemento(a, c1), c1->apellidos);
    }
    
    printf("\n");
    
    printf("Ingrese el DNI de la persona a borrar: ");
    scanf("%d", &dni);
    
    c1 = l_int_primero(a);
    
    while (c1 != l_int_ultimo(a)) {
        if (l_int_elemento(a, c1->psig) == dni) {
            l_int_borrar(a, c1->psig);
            break;
        }
        c1 = l_int_siguiente(a, c1);
    }
    
    printf("Lista después de borrar:\n");
    
    c1 = l_int_primero(a);
    
    for (conta = 0; conta < l_int_longitud(a); conta++) {
        c1 = l_int_siguiente(a, c1);
        printf("DNI: %d, Apellidos: %s\n", l_int_elemento(a, c1), c1->apellidos);
    }
    
    l_int_destruir(a);
    
    system("PAUSE");
    
    return (EXIT_SUCCESS);
}
