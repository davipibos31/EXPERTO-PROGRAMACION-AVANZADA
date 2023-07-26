#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 500
#define LIBRE -1
#define BORRADO -2

typedef struct {
    char clave[510];
    char apellidos[255];
    char nombre[255];
    int edad;
    char goya[1];
    long cache;
} myreg;

void init(myreg t_hash[], int tam);
int H(char* k, int tam);
int nextPos(int pos, int tam);
void insert(myreg r, myreg t_hash[], int tam);
int search(char* k, myreg t_hash[], int tam);
int remove_item(char* k, myreg t_hash[], int tam);
float loadfactor(myreg t_hash[], int tam);
void show(myreg t_hash[], int tam);
int leerFichero(char *nombre_fichero);

int main(int argc, char *argv[]) {
    leerFichero("listaActores.csv");
    system("PAUSE");
    return EXIT_SUCCESS;
}

void init(myreg t_hash[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        strcpy(t_hash[i].clave, "");
        strcpy(t_hash[i].apellidos, "");
        strcpy(t_hash[i].nombre, "");
        t_hash[i].edad = LIBRE;
        strcpy(t_hash[i].goya, "");
        t_hash[i].cache = LIBRE;
    }
}

int H(char* k, int tam) {
    int sum = 0;
    int i;
    for (i = 0; k[i] != '\0'; i++) {
        sum += k[i];
    }
    return sum % tam;
}

int nextPos(int pos, int tam) {
    return (pos + 1) % tam;
}

void insert(myreg r, myreg t_hash[], int tam) {
    int pos = H(r.clave, tam);
    int i = 0;
    
    while (strcmp(t_hash[pos].clave, "") != 0 && strcmp(t_hash[pos].clave, "BORRADO") != 0) {
        pos = nextPos(pos, tam);
        i++;
        if (i >= tam) {
            printf("Tabla llena\n");
            return;
        }
    }

    t_hash[pos] = r;
}

int search(char* k, myreg t_hash[], int tam) {
    int pos = H(k, tam);
    int i = 0;
    
    while (strcmp(t_hash[pos].clave, "") != 0) {
        if (strcmp(t_hash[pos].clave, k) == 0) {
            return pos;
        }
        
        pos = nextPos(pos, tam);
        i++;
        if (i >= tam) {
            break;
        }
    }

    return -1;
}

int remove_item(char* k, myreg t_hash[], int tam) {
    int pos = search(k, t_hash, tam);
    if (pos == -1) {
        return -1;
    }
    
    strcpy(t_hash[pos].clave, "BORRADO");
    strcpy(t_hash[pos].nombre, "BORRADO");
    strcpy(t_hash[pos].apellidos, "BORRADO");
    t_hash[pos].edad = BORRADO;
    strcpy(t_hash[pos].goya, "BORRADO");
    t_hash[pos].cache = BORRADO;
    
    return 1;
}

float loadfactor(myreg t_hash[], int tam) {
    int n_elems = 0;
    int i;
    
    for (i = 0; i < tam; i++) {
        if (strcmp(t_hash[i].clave, "") != 0 && strcmp(t_hash[i].clave, "BORRADO") != 0) {
            n_elems++;
        }
    }
    
    return ((float)n_elems / tam);
}

void show(myreg t_hash[], int tam) {
    int i;
    
    for (i = 0; i < tam; i++) {
        printf("%s %s %s %d %s %ld | ", t_hash[i].clave, t_hash[i].nombre, t_hash[i].apellidos, t_hash[i].edad, t_hash[i].goya, t_hash[i].cache);
    }
    
    printf("\n");
}

int leerFichero(char *nombre_fichero) {
    myreg reg1;
    char linea[500];
    char *token;

    FILE *fp = fopen(nombre_fichero, "r");
    if (fp == NULL) {
        printf("Error de lectura del archivo\n");
        return -1;
    }

    myreg myhash[TAM];
    init(myhash, TAM);

    while (fgets(linea, 500, fp) != NULL) {
        token = strtok(linea, ";");
        strcpy(reg1.apellidos, token);

        token = strtok(NULL, ";");
        strcpy(reg1.nombre, token);

        strcpy(reg1.clave, reg1.apellidos);
        strcat(reg1.clave, reg1.nombre);

        token = strtok(NULL, ";");
        reg1.edad = atoi(token);

        token = strtok(NULL, ";");
        strcpy(reg1.goya, token);

        token = strtok(NULL, ";");
        reg1.cache = atoi(token);

        insert(reg1, myhash, TAM);
    }

    show(myhash, TAM);
    fclose(fp);
    return 0;
}
