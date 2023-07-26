#include "hashing.h"
#include <stdlib.h>
#include <stdio.h>

void init(myreg t_hash[], int tam){
     int i;
     for(i=0; i < tam; i++) {
              t_hash[i].key = LIBRE;
     }
}

int H(int k, int tam){
     return (k%tam);
}

void insert(myreg r, myreg t_hash[], int tam) {
     int pos;
     
     pos = H(r.key, tam);
     if(t_hash[pos].key == LIBRE || t_hash[pos].key == BORRADO) {
              t_hash[pos] = r;
     }
     else // Esta ocupada
          printf("Colision\n");
}
              

int search(int v, myreg t_hash[], int tam) {
    int pos;
     
     pos = H(v, tam);
     
     if(t_hash[pos].key == LIBRE) return -1; // No esta en la tabla
     
     if(t_hash[pos].key == v) return pos;
     
     else {
          printf("Colision\n");
          return -1; // CAMBIAR SEGUN ESTRATEGIA COLISION
     }
}


int remove(int v, myreg t_hash[], int tam){
    
    int pos;
     
    pos = search(v,t_hash,tam);
    if(pos == -1) return -1;
    t_hash[pos].key = BORRADO;
    return 1;
}

// N/M, donde N es el numero de elemento insertados
// M es el tamano de la tabla hash
float loadfactor(myreg t_hash[], int tam) {
      int n_elems = 0;
      int i;
      
      for(i = 0; i < tam; i++){
          if(t_hash[i].key != LIBRE  &&  t_hash[i].key != BORRADO)
               n_elems++;
      }
      
      return ((float)n_elems/tam);
}
      
void show(myreg t_hash[], int tam){
     int i;
      
      for(i = 0; i < tam; i++){
            printf("%d | ", t_hash[i]);
      } 
      printf("\n");                      
}
