#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

// Funci�n para mostrar la tabla siguiente
void mostrar_tabla(int *t, int size, const char *nombre_tabla) {
     printf("Tabla %s: ",nombre_tabla);
     for(int i = 0; i < size; i++) {
             printf("%i ", t[i]); 
     }
     printf("\n");
}



// p es el patr�n, size es el tama�o del patron y tablaNext es la tabla "siguiente" asociada a p
// Esta funci�n se encarga de calcular la tabla siguiente
void preKMP(char *p, int size, int *tablaNext){
	int i,j;
	i = 0;
	j = tablaNext[0] = -1;
	while (i < size-1) {
		while (j > -1 && p[i] != p[j]) { 
			j = tablaNext[j];           
		}
		i++;
		j++;
		if (p[i] == p[j])   
			 tablaNext[i] = tablaNext[j];             
		else                
			tablaNext[i] = j;		       
	}
}


// s es la cadena madre, p es el patr�n, y posiciones es un array de enteros
// que contendr� las posiciones iniciales del patr�n p detectado en la cadena s 
void KMPSearch(char *s, char *p, int *posiciones) {
     int i,j,k; // i �ndice de S, j �ndice de P, k �ndice de posiciones
     
     int  s_len, p_len;   // Obtener las longitudes de s y p
     p_len = strlen(p);
     s_len = strlen(s);          
     
     int tablaNext[p_len];  // Crear la tabla siguiente de P y calcularla     
     preKMP(p, p_len, tablaNext);
     mostrar_tabla(tablaNext, p_len, "Sgte");
     i = j = k = 0;
     while (i < s_len) {
	       while (j > -1 && s[i] != p[j]) {                 
		         j = tablaNext[j];
           }
           i++;
           j++;
           if (j >= p_len) {
              posiciones[k] = i -j;  // Grabamos la primera posici�n del patr�n encontrado
              k++;
			  j = 0;
	      }
    }
}


int main (int argc, char *argv[])
{    
    
     int *posiciones;  // TO_DO: En esta variable se debe crear un array para 
                      // almacenar las posiciones del texto donde se
                      // encuentra el patr�n e iniciarlo a un valor no representativo
     
     // TO_DO: Abrir el fichero de texto fuente y almacenarlo en un array
     
     // TO_DO: LlAmar a KMPSearch con el texto de b�squeda del fichero "textobusq.txt",
     // el patr�n "papadopaulus" y el array de posiciones
    
    system("PAUSE");
    return 0;
}