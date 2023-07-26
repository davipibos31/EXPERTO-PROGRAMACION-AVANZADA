#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM 50

typedef struct Node {
    char clave[510];
    char apellidos[255];
    char nombre[255];
    int edad;
    char goya[1];
    long cache;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

typedef struct {
    LinkedList* table[TAM];
} HashTable;

void init(HashTable* hashTable) {
    for (int i = 0; i < TAM; i++) {
        hashTable->table[i] = NULL;
    }
}

int hash(char* clave) {
    int sum = 0;
    for (int i = 0; i < strlen(clave); i++) {
        sum += (int)clave[i];
    }
    return sum % TAM;
}

Node* createNode(char* clave, char* apellidos, char* nombre, int edad, char* goya, long cache) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->clave, clave);
    strcpy(newNode->apellidos, apellidos);
    strcpy(newNode->nombre, nombre);
    newNode->edad = edad;
    strcpy(newNode->goya, goya);
    newNode->cache = cache;
    newNode->next = NULL;
    return newNode;
}

void insert(HashTable* hashTable, char* clave, char* apellidos, char* nombre, int edad, char* goya, long cache) {
    int pos = hash(clave);
    if (hashTable->table[pos] == NULL) {
        LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
        list->head = createNode(clave, apellidos, nombre, edad, goya, cache);
        hashTable->table[pos] = list;
    }
    else {
        Node* newNode = createNode(clave, apellidos, nombre, edad, goya, cache);
        Node* current = hashTable->table[pos]->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void show(HashTable* hashTable) {
    for (int i = 0; i < TAM; i++) {
        LinkedList* list = hashTable->table[i];
        if (list != NULL) {
            Node* current = list->head;
            while (current != NULL) {
                printf("%s %s %s %d %s %ld\n", current->clave, current->apellidos, current->nombre, current->edad, current->goya, current->cache);
                current = current->next;
            }
        }
    }
}

int leerFichero(char* nombre_fichero) {
    Node reg1;
    char linea[500];
    char* token;

    FILE* fp = fopen(nombre_fichero, "r");
    if (fp == NULL) {
        printf("Error de lectura del archivo\n");
        return -1;
    }

    HashTable hashTable;
    init(&hashTable);

    while (fgets(linea, 500, fp) != NULL) {
        token = strtok(linea, ";");
        char apellidos[255];
        strcpy(apellidos, token);

        token = strtok(NULL, ";");
        char nombre[255];
        strcpy(nombre, token);

        char clave[510];
        strcpy(clave, apellidos);
        strcat(clave, nombre);

        token = strtok(NULL, ";");
        int edad = atoi(token);

        token = strtok(NULL, ";");
        char goya[1];
        strcpy(goya, token);

        token = strtok(NULL, ";");
        long cache = atol(token);

        insert(&hashTable, clave, apellidos, nombre, edad, goya, cache);
    }

    show(&hashTable);

    return 0;
}

int main() {
    clock_t start_time, end_time;
    int total_collisions = 0;

    start_time = clock();
    leerFichero("listaActores.csv");
    end_time = clock();

    double elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC);
    printf("Tiempo empleado: %lf segundos\n", elapsed_time);
    printf("Total de colisiones: %d\n", total_collisions);

    return 0;
}
