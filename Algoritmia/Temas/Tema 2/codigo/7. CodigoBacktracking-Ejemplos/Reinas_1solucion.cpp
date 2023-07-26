#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

// Variable global para contar el número de nodos generados
// ¿Cómo se podría evitar que fuera global?
int num_nodos = 0;

// Declaración de todas las funciones utilizadas
void mostrar_sol(int *reinas,int n_reinas);
int valido(int *reinas, int fila);
int reinaBT(int *reinas, int fila,int n_reinas);


// Comprueba si el tablero actual es valido (no se amenazan las reinas)
int valido(int *reinas, int fila)
{
    for(int i=0;i<fila;i++){
        if((reinas[i]==reinas[fila])||   // Misma fila
           (abs(fila-i)==abs(reinas[fila]-reinas[i])))  // Misma diagonal
                return FALSE;                
    }
    return TRUE;
}

// Función backtracking recursiva para encontrar la solución
int reinaBT(int *reinas, int fila,int n_reinas)
{
    int exito=FALSE;
    if(fila > (n_reinas-1)){   // Nos hemos salido del tablero
          return FALSE;
    }
    
    reinas[fila]=-1;  // Inciamos los posibles valores de cada casilla a -1
    do{
       reinas[fila]=reinas[fila]+1;   // Vamos probando la reina en "fila" en diversas columnas 
       num_nodos++;                   // Contamos el nuevo nodo backtracking generado 
       //mostrar_sol(reinas,n_reinas);                        
       if(valido(reinas,fila)){       // Comprobar si el tablero es válido
                  
                  if(fila==n_reinas-1){    // Todas las reinas colocadas
                        mostrar_sol(reinas,n_reinas);                      
                        exito=TRUE;
                  }
                  else{                // Quedan soluciones parciales
                       exito=reinaBT(reinas,fila+1,n_reinas);
                  }
       }
    }while((exito==FALSE)&&(reinas[fila]!=(n_reinas-1)));  // Hasta que recorran todas las columnas
    return exito;                                          
}

// Para mostrar el tablero por pantalla
void mostrar_sol(int *reinas,int n_reinas)
{
     for(int i=0;i<n_reinas;i++){
             for (int j=0;j<n_reinas;j++){
                 if(reinas[i]==j){
                     printf("#");
                 }
                 else{
                      printf("-");
                 }
             }
             printf(" Fila: %d  Columna: %d\n",i,reinas[i]);
     }
}     


int main (int argc, char *argv[])
{
    int n_reinas,exito;
    int *reinas;
    
    printf("Introduzca el número de reinas a colocar:");
    scanf("%d", &n_reinas);
    
    // Reservamos espacio para el array de soluciones, llamado reinas
    reinas = (int*) malloc(n_reinas*sizeof(int));
    
    // Inciamos el array de soluciones a -1
    for(int i=0;i<n_reinas;i++){
            reinas[i]=-1;
    }
        
    // Comienza el backtracking            
    exito = reinaBT(reinas,0,n_reinas);
                 
    if(exito!=1)
           printf("No exite solucion\n");
              
    printf("\nNumero de nodos: %d\n", num_nodos);      
      
    system("PAUSE");
    return 0;
}
