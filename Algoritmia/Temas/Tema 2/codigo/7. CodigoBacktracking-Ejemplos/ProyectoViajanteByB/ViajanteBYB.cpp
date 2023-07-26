// LA MATRIZ DE DISTANCIA ES LA QUE APARECE EN EL TEMA 1, DIAPOSITIVA 93
// LA CIUDAD 1 ES LA 0, LA 2 ES LA 1, ETC.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cola_dinamica.h"

#define TRUE 1
#define FALSE 0

#define NUM_CIUDADES 5
#define MAX_DISTANCIA 1000000

#define MAX_COLA 100


int visitado(int ciudad, int *sol, int nivel){
    for(int i=0; i <= nivel; i++) {
            if (ciudad == sol[i]) 
               return true;
    }
    return false;    
}

int calcularCotaInf(Nodo n, int D[][NUM_CIUDADES]){
    int cotaInf, minFila;
    cotaInf = n.longitud;
    for(int i = 0; i < NUM_CIUDADES; i++) {
            if (!visitado(i, n.solucion, (n.nivel) -1)) {
                             minFila = MAX_DISTANCIA ;
                             for (int j=0; j < NUM_CIUDADES; j++) {
                                if ((i!=j) && ((!visitado(j,n.solucion,n.nivel)) || (j==0))) {
                                           minFila = fmin(minFila, D[i][j]);
                                           
                                }
                             
                             }            
            cotaInf += minFila;                                  
            }
    }
    return cotaInf;
}

int calcularHijos(Nodo padre, Nodo* hijos, int D[][NUM_CIUDADES]) {     
     int contadorHijos =0;     
     for(int i=0; i < NUM_CIUDADES; i++) {
             if((!visitado(i,padre.solucion,padre.nivel)) && 
                (D[padre.solucion[padre.nivel]][i] != 0)) {
                   for(int j=0; j < NUM_CIUDADES; j++) 
                           hijos[contadorHijos].solucion[j] = padre.solucion[j];
                   hijos[contadorHijos].solucion[(padre.nivel)+1] = i;
                   hijos[contadorHijos].nivel = (padre.nivel)+1;
                   hijos[contadorHijos].longitud = padre.longitud + 
                                                   D[padre.solucion[padre.nivel]][i];
                   hijos[contadorHijos].cota_inf = calcularCotaInf(hijos[contadorHijos],D);
                   contadorHijos++;                             
             }
     }
     return contadorHijos;
}

Nodo crearNodoRaiz(int D[][NUM_CIUDADES]){
     Nodo raiz;
     
     raiz.solucion[0] = 0;
     for(int i = 1; i < NUM_CIUDADES; i++) {
             raiz.solucion[i]  =-1;
     }
     raiz.nivel = 0;
     raiz.longitud = 0;
     raiz.cota_inf = calcularCotaInf(raiz,D);
     return raiz;
}



void mostrar_sol(int *sol, int D[][NUM_CIUDADES]) {
     printf("\nCiudades:[");
     for (int i=0; i<NUM_CIUDADES; i++){
        printf("%d ", sol[i]); 
     }
     printf("0]\n");
     
     int distancia = 0;
     for(int i= 1; i < NUM_CIUDADES; i++) {
             distancia += D[sol[i-1]][sol[i]];
     }
     distancia += D[sol[NUM_CIUDADES-1]][0];
     printf("Distancia : %d\n", distancia);
}
    
int viajanteBYB(int D[][NUM_CIUDADES], int *sol){
    
    Nodo x, hijos[NUM_CIUDADES];
    int cota, numHijos, longCamino;
    tipo_cola LNV;
    
    x = crearNodoRaiz(D);
    //imprimir_nodo(x);
    crear(&LNV);

    push(&LNV,x);
    cota = MAX_DISTANCIA;
    while(!es_vacia(&LNV)) {
          //printf("COTA_ACUTAL: %d\n", cota);
          x = pop(&LNV);
          //imprimir_nodo(x);
          if(x.cota_inf < cota) {
                   numHijos = calcularHijos(x,hijos,D);
                   for(int i = 0; i < numHijos; i++) {
                           //printf("HIJO:\n");
                           //imprimir_nodo(hijos[i]); 
                           
                           if((hijos[i].nivel == NUM_CIUDADES -1) && 
                             (hijos[i].cota_inf < cota)) {                                  
                                 longCamino = hijos[i].longitud + 
                                              D[hijos[i].solucion[NUM_CIUDADES-1]][0];
                                              
                                 if(longCamino < cota) {
                                               for(int j=0; j < NUM_CIUDADES; j++) 
                                                       sol[j] = hijos[i].solucion[j];
                                               cota = longCamino;        
                                 }
                           }
                           else {
                                 if((hijos[i].nivel < NUM_CIUDADES -1) && 
                                    (hijos[i].cota_inf < cota)) {                                           
                                          push(&LNV,hijos[i]);             
                                 }
                           }
                     //system("PAUSE");                 
                   }
          }                    
                      
    }
}    
    


int main (int argc, char *argv[])
{   
    int solucion[NUM_CIUDADES]; 
    int D[NUM_CIUDADES][NUM_CIUDADES];
    
    
    // LA MATRIZ DE DISTANCIA ES LA QUE APARECE EN EL TEMA 1, DIAPOSITIVA 93
    // LA CIUDAD 1 ES LA 0, LA 2 ES LA 1, ETC.

   
    D[0][0]= 0; D[0][1]= 14; D[0][2]= 4; D[0][3]= 10; D[0][4]= 20; 
    D[1][0]= 14; D[1][1]= 0; D[1][2]= 7; D[1][3]= 8; D[1][4]= 7; 
    D[2][0]= 4; D[2][1]= 5; D[2][2]= 0; D[2][3]= 7; D[2][4]= 16; 
    D[3][0]= 11; D[3][1]= 7; D[3][2]= 9; D[3][3]= 0; D[3][4]= 2;
    D[4][0]= 18; D[4][1]= 7; D[4][2]= 17; D[4][3]= 4; D[4][4]= 0; 
   
    for(int i=0; i < NUM_CIUDADES; i++) {
            solucion[i] = -1;
    }
    
    viajanteBYB(D,solucion);
    mostrar_sol(solucion, D);
    system("PAUSE");  
    
    
    
    return 0;
}
