// Cola dinamica
#include <stdio.h>
#include <stdlib.h>
#include "cola_dinamica.h"


void crear(tipo_cola *q) {
     q->cabeza = NULL;
     q->cola = NULL;
}

int es_vacia(tipo_cola *q){

    return (q->cabeza==NULL); // Si la cabeza está a Null, cola vacía
}

void push(tipo_cola *q, Nodo n){

    P_nodo_cola paux;
    paux = (P_nodo_cola)malloc(sizeof(nodo_cola)); //Reservamos memoria
    
    paux->valor = n;
    paux->sgte = NULL; //el último nodo nunca apunta a nadie
    
    if (es_vacia(q)){ // Si es vacia, la cabeza y cola apuntan al único nodo creado

        q->cabeza=q->cola= paux; 
        
    }else {
        q->cola->sgte = paux; //con el ultimo apuntamos al siguiente nodo creado que es paux (el que era el ultimo lo apuntamos al nuevo)
        q->cola = paux; //el nodo creado lo introducimos en la última posicion y ahora es la cola
    
    }
}

Nodo pop(tipo_cola *q){

    P_nodo_cola p;
    Nodo v;
    
    if (es_vacia(q)) {        
        printf("Error, cola vacía\n");
        v.nivel = -1;       
    }else {
        v= q->cabeza->valor; //metemos el valor de la cabeza en v
        p= q->cabeza; // metemos la posicion de la cabeza en p
        q->cabeza=q->cabeza->sgte; //Apuntamos al siguiente nodo
        
        free(p);  //Liberamos la posicion de p
    }
    return (v);
    

}


void vaciar(tipo_cola *q){

    P_nodo_cola p, t;
    
    p=q->cabeza;
    while (p!=NULL) {
        t=p;        
        p=p->sgte;  //avanzamos p        
        free(t);
    }
    q->cabeza = q->cola = NULL;

}


void imprimir_nodo(Nodo n) {
     printf("\tNivel: %d\n", n.nivel);
     printf("\tLongitud: %d\n", n.longitud);
     printf("\tCota: %d\n", n.cota_inf);
     printf("\tSolucion: ");
     for(int i = 0; i < n.nivel; i++) {
             printf("%d ", n.solucion[i]);
     }
     printf("\n");
     
     
     
}

void imprimir_cola(tipo_cola cola){
	//Un puntero a nodo axuilizar
	P_nodo_cola paux;
	
	//Mientras nodoAuxiliar = cabeza, y no sea NULL, se iguala al siguiente
	for (paux = cola.cabeza;paux!=NULL;paux=paux->sgte){
		printf("%Nodo Info:\n");
		imprimir_nodo(paux->valor);
	}
	printf("\n");
}


Nodo elemento(tipo_cola *q){

    Nodo v;
    //Si esta vacia se muestra un error
    if(es_vacia(q)){        
        printf("Error: cola vacia\n");
        v.nivel = -1;
    }
    else{
         //Asiganmos el valor del nodo actual
         v = q->cabeza->valor;
    }
    return v;
}



