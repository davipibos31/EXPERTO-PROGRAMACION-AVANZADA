#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define ALPHABET_SIZE 25  // Tama�o del alfabeto espanol



// Funcion para calcular la tabla D1 (regla del mal caracter). 
// p es el patron, size es el tama�o del patr�n y D1 es la tabla que se debe rellenar 
// en la funcion
static void prepare_badcharacter_heuristic(const char *p, int size, int D1[ALPHABET_SIZE]) {
 
 int i;
 
 for (i = 0; i < ALPHABET_SIZE; i++)
     D1[i] = -1;
 
 for (i = 0; i < size; i++) {
     int t = (size_t)p[i] - 97 ; // Obtiene el c�digo ascii de la letra del patron en la posicion i          
     D1[t] = i;     
 }
     
}

// Funcion auxiliar necesaria para calcular la tabla D2. 
static void compute_prefix(const char* str, int size, int result[]) {
 int q;
 int k;
 result[0] = 0;
 
 k = 0;
 for (q = 1; q < size; q++) {
     while (k > 0 && str[k] != str[q])
         k = result[k-1];
 
     if (str[k] == str[q])
         k++;
     result[q] = k;
 }
}
 
// Funcion para calcular la tabla D2 (regla del buen sufijo). 
// p es el patron, size es el tama�o del patr�n y D2 es la tabla que se debe rellenar 
// en la funcion
void prepare_goodsuffix_heuristic(const char *p, int size, int D2[]) {
 
 char *left = (char *) p;
 char *right = left + size;
 char reversed[size+1];
 char *tmp = reversed + size;
 int i;
 
 *tmp = 0;
 while (left < right)
     *(--tmp) = *(left++);
 
 int prefix_normal[size];
 int prefix_reversed[size];
 
 compute_prefix(p, size, prefix_normal);
 compute_prefix(reversed, size, prefix_reversed);
 
 for (i = 0; i <= size; i++) {
     D2[i] = size - prefix_normal[size-1];
 }
 
 for (i = 0; i < size; i++) {
     const int j = size - prefix_reversed[i];
     const int k = i - prefix_reversed[i]+1;
 
     if (D2[j] > k)
         D2[j] = k;
 }
}


// Funci�n para mostrar las tablas D1 o D2
void mostrar_tabla(int *s, int size, const char *nombre_tabla) {
     printf("Tabla %s: ",nombre_tabla);
     for(int i = 0; i < size; i++) {
             printf("%i ", s[i]); 
     }
     printf("\n");
}



/*
 * Algoritmo de busqueda Boyer-Moore
 * s es la cadena madre, p es el patr�n, y posiciones es un array de enteros
 * que contendr� las posiciones iniciales del patr�n p detectado en la cadena s cuando acabe el algoritmo
 */
void boyermoore_search(char *s, char *p, int posiciones[]) {
 /*
 * Calcula el tama�o de las cadenas
 */
 int  s_len, p_len;
 p_len = strlen(p);
 s_len = strlen(s);
 
 /*
 * Comprobaciones simples
 */
 if(s_len == 0)
     return;
 if(p_len == 0)
     return;
 if(p_len > s_len)
     return;
     
 
 //Obtener tablas D1 y D2
 
 int D1[ALPHABET_SIZE];  // D1 = mal caracter
 int D2[p_len+1]; // D2 = buen sufijo
 
 
 prepare_badcharacter_heuristic(p, p_len, D1); 
 prepare_goodsuffix_heuristic(p, p_len, D2);
 
 mostrar_tabla(D1,ALPHABET_SIZE, "D1");
 mostrar_tabla(D2,p_len, "D2");
  
 // Busqueda Boyer-Moore
 
 int i = 0; // indice de la cadena s
 int k = 0; // indice del vector resultado "posiciones"
 while(i <= (s_len - p_len))
 {
     int j = p_len;  // indice del patron p (desde el ultimo caracter)
     while(j > 0 && p[j-1] == s[i+j-1])
         j--;
 
     if(j > 0)
     {
         int z = D1[((size_t) s[i+j-1])-97];
         int m;
         if(z < j && (m = j-z-1) > D2[j])
             i+= m;
         else
             i+= D2[j];
     }
     else
     {
         posiciones[k] = i; // Grabamos la posici�n incial donde se ha encontrado el patr�n
         k++;
         i++;         
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