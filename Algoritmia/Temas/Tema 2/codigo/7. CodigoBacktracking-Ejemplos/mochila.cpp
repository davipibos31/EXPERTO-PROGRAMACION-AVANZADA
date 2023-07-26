#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OBJETOS 4
#define CAPACIDAD 7


// Variable global para contar el número de nodos generados
int numero_nodos = 0;

typedef struct
{
   int peso;
   int beneficio;
} Objeto;



// Para mostrar contenido mochila por pantalla
void mostrar_sol(int *mochila, int peso_total, int beneficio_total){ 
     //int peso_total = 0;
     //int beneficio_total = 0;
     printf("Objetos seleccionados: ");
     for(int i = 0; i < NUM_OBJETOS; i++){
             if(mochila[i] == 1){
                   printf("%d ", i+1);
                  // peso_total+= peso_total + objetos[i].peos;
                   //beneficio_total+= beneficio_total + objetos[i].beneficio;
             }             
     }
          
     printf("\nPeso Final: %d; Beneficio Final: %d\n", peso_total, beneficio_total);
}     


int valido(int solucion[], int etapa, Objeto objetos[]){
     
      int peso_total = 0, benef_total = 0;;
      for(int i =0;i<=etapa;i++){        
        if(solucion[i]==1)
              peso_total += objetos[i].peso;                    
      }
            
      if(peso_total > CAPACIDAD)                                        
         return 0;
      else
         return 1;   
}

void actualizarSolucion(int solucion[], Objeto objetos[], int mochila_final[], int *peso_final, int *benef_final) {
 
      int benef_total = 0;
      int peso_total = 0;
      for(int i =0;i< NUM_OBJETOS ;i++){        
        if(solucion[i]==1) {
              benef_total += objetos[i].beneficio;        
              peso_total += objetos[i].peso;
        }
      }
      
      if(benef_total > *benef_final) {
             for(int i = 0; i<NUM_OBJETOS; i++)
                     mochila_final[i] = solucion[i];
             *benef_final = benef_total;
             *peso_final = peso_total;             
      }                                                                   
}


void mochilaRec(int solucion[], int etapa, Objeto objetos[], int mochila_final[], int *peso_final, int *benef_final){

     int i=0;

     if (etapa > NUM_OBJETOS-1)  return;   
 
     do{           
        solucion[etapa]=i; 
        numero_nodos=numero_nodos+1;  
        if(valido(solucion,etapa,objetos)){                          
                //system("PAUSE");                                                                     
                if(etapa==NUM_OBJETOS-1) 
                        actualizarSolucion(solucion,objetos,mochila_final,peso_final,benef_final);                                                                                                         
                
                else
                        mochilaRec(solucion,etapa+1,objetos,mochila_final,peso_final,benef_final); 
                                                      
        }
        i++;
     } while(solucion[etapa]!=1);
     solucion[etapa]=-1;
}

int main(){    
  int peso = 0, beneficio = 0;  
  Objeto objetos[NUM_OBJETOS];  
  int solucion_parcial[NUM_OBJETOS], mochila[NUM_OBJETOS];
  for(int i=0; i<NUM_OBJETOS; i++)  {          
    objetos[i].peso = i +2;
    objetos[i].beneficio = i +3;          
    solucion_parcial[i] = -1;
    mochila[i] = -1;
  }   
  
  
  mochilaRec(solucion_parcial,0,objetos,mochila,&peso,&beneficio);
  
  mostrar_sol(mochila,peso,beneficio);
  printf("Nodos %d\n",numero_nodos);  
  system("PAUSE");
  return 0;
}


