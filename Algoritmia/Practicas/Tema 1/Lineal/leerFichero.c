#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 500

int numlinea = 0;

int leerFichero(char *nombre_fichero) {
    myreg reg1;
    char linea[500]; // Para guardar la linea de cada fichero
    char *token;     // Para cada token de cada linea

    //Abrimos el fichero
    FILE *fp = fopen(nombre_fichero,"r");

    // Comprobar que no hay error al abrir
    if(fp == NULL){
            printf("Error de lectura del archivo");
            return -1;
    }

    // Recorremos cada linea del fichero
    while(fgets(linea,500,fp)!=NULL){
        
        printf("Linea leida: %s\n", linea);
        
        // Token del apellido
        
        token = strtok(linea, ";");
        strcpy(reg1.apellidos, token);
        printf("%s\n",reg1.apellidos);
        
        // Token del nombre
        
        token = strtok(NULL, ";");
        strcpy(reg1.nombre, token);
        printf("%s\n",reg1.nombre);

        // Clave única compuesta de apellido y nombre
        
        strcpy(reg1.clave, reg1.apellidos);
        strcat(reg1.clave, reg1.nombre);
        
        // Token de la edad
        
        token = strtok(NULL, ";");
        reg1.edad = atoi(token);
        printf("%d\n",reg1.edad);
        
        // Token del goya
        
        token = strtok(NULL, ";");
        strcpy(reg1.goya, token);
        printf("%s\n",reg1.goya);

        // Token del cache
        
        token = strtok(NULL, ";");
        reg1.cache = atoi(token);
        printf("%d\n",reg1.cache);

        // Funciones hash para iniciar e insertar y mostrar        

        myreg myhash[TAM];
        init(myhash, TAM);
        insert(reg1, myhash, TAM);
        show(myhash, TAM);
        //system("PAUSE");     // COMENTAR PARA EJECUCION REAL
    }

    return 0;
}

int main(int argc, char *argv[]) {
    leerFichero("listaActores.csv");
    system("PAUSE");
    return EXIT_SUCCESS;

  return 0;
}