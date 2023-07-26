#include "hashing.h"
#include <stdlib.h>
#include <stdio.h>

int value;
void init(myreg t_hash[], int tam){
     int i;
     
     for(i=0; i < tam; i++) {
          value = atoi(t_hash[i].clave);
     }
}

int H(int k, int tam){
     return (k%tam);
}

void insert(myreg r, myreg t_hash[], int tam) {
     int pos;
     
     pos = H(r.clave, tam);
     if(t_hash[pos].clave == LIBRE || t_hash[pos].clave == BORRADO) {
              t_hash[pos] = r;
              t_hash[pos].edad = r.edad;
     }
     else // Esta ocupada
          printf("Colision\n");
}
              

int search(myreg r, myreg t_hash[], int tam) {
    int pos;
     
     pos = H(r.clave, tam);
     
     if(t_hash[pos].clave == LIBRE) return -1; // No esta en la tabla
     
     if(t_hash[pos].clave == r.clave) return pos;
     
     else {
          printf("Colision\n");
          return -1; // CAMBIAR SEGUN ESTRATEGIA COLISION
     }
}


int remove(myreg r, myreg t_hash[], int tam){
    
    int pos;
     
    pos = search(r,t_hash,tam);
    if(pos == -1){
     return -1;
    }
     value = atoi(t_hash[pos].clave);
          value = BORRADO;
     value = atoi(t_hash[pos].nombre);
          value = BORRADO;
     value = atoi(t_hash[pos].apellidos);
          value = BORRADO;
    t_hash[pos].edad = BORRADO;
    value = atoi(t_hash[pos].goya);
          value = BORRADO;
    t_hash[pos].cache = BORRADO;
    return 1;
}

// N/M, donde N es el numero de elemento insertados
// M es el tamano de la tabla hash
float loadfactor(myreg t_hash[], int tam) {
      int n_elems = 0;
      int i;
      
      for(i = 0; i < tam; i++){
          if(t_hash[i].clave != LIBRE  &&  t_hash[i].clave != BORRADO)
               n_elems++;
          if(t_hash[i].apellidos != LIBRE  &&  t_hash[i].apellidos != BORRADO)
               n_elems++;
          if(t_hash[i].nombre != LIBRE  &&  t_hash[i].nombre != BORRADO)
               n_elems++;
          if(t_hash[i].edad != LIBRE  &&  t_hash[i].edad != BORRADO)
               n_elems++;
          if(t_hash[i].goya != LIBRE  &&  t_hash[i].goya != BORRADO)
               n_elems++;
          if(t_hash[i].cache != LIBRE  &&  t_hash[i].cache != BORRADO)
               n_elems++;
      }
      
      return ((float)n_elems/tam);
}
      
void show(myreg t_hash[], int tam){
     int i;
      
      for(i = 0; i < tam; i++){
            printf("%s %s %s %d %s %d | ", t_hash[i].clave,  t_hash[i].nombre, t_hash[i].apellidos, t_hash[i].edad, t_hash[i].goya, t_hash[i].cache);
      } 
      printf("\n");                      
}
