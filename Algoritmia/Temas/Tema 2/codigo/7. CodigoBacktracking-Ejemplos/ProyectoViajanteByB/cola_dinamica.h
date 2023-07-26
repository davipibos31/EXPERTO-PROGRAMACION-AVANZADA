// Cola dinamica
#include <stdio.h>
#include <stdlib.h>


typedef struct 
{
   int solucion[10];
   int nivel;
   int longitud;
   int cota_inf;
} Nodo;


typedef struct n_cola{

    Nodo valor;
    struct n_cola *sgte;

}nodo_cola, *P_nodo_cola;
// Estructura de un nodo de la cola y su puntero

typedef struct t_cola{

    P_nodo_cola cabeza; 
    P_nodo_cola cola;

}tipo_cola;
// Estructura que contiene la cabeza y la cola de la cola


void crear(tipo_cola *q);

int es_vacia(tipo_cola *q);

void push(tipo_cola *q, Nodo n);

Nodo pop(tipo_cola *q);

void vaciar(tipo_cola *q);

void imprimir_nodo(Nodo n);

void imprimir_cola(tipo_cola cola);

Nodo elemento(tipo_cola *q);

