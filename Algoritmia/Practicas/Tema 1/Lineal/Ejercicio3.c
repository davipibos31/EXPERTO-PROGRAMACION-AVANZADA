#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50
#define LIBRE NULL

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

void init(HashTable* hashTable);
int hash(char* k);
Node* createNode(char* clave, char* apellidos, char* nombre, int edad, char* goya, long cache);
void insert(HashTable* hashTable, char* clave, char* apellidos, char* nombre, int edad, char* goya, long cache);
void show(HashTable* hashTable);
int leerFichero(char* nombre_fichero);

int main(int argc, char* argv[]) {
    HashTable hashTable;
    init(&hashTable);
    leerFichero("listaActores.csv");
    show(&hashTable);
    system("PAUSE");
    return EXIT_SUCCESS;
}

void init(HashTable* hashTable) {
    int i;
    for (i = 0; i < TAM; i++) {
        hashTable->table[i] = (LinkedList*)malloc(sizeof(LinkedList));
        hashTable->table[i]->head = LIBRE;
    }
}

int hash(char* k) {
    int sum = 0;
    int i;
    for (i = 0; k[i] != '\0'; i++) {
        sum += k[i];
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
    Node* newNode = createNode(clave, apellidos, nombre, edad, goya, cache);

    if (hashTable->table[pos]->head == LIBRE) {
        hashTable->table[pos]->head = newNode;
    } else {
        Node* temp = hashTable->table[pos]->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void show(HashTable* hashTable) {
    int i;
    for (i = 0; i < TAM; i++) {
        printf("Posición %d: ", i);
        Node* temp = hashTable->table[i]->head;
        while (temp != NULL) {
            printf("%s %s %s %d %s %ld | ", temp->clave, temp->nombre, temp->apellidos, temp->edad, temp->goya, temp->cache);
            temp = temp->next;
        }
        printf("\n");
    }
}

int leerFichero(char* nombre_fichero) {
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
        long cache = atoi(token);

        insert(&hashTable, clave, apellidos, nombre, edad, goya, cache);
    }

    show(&hashTable);
    fclose(fp);
    return 0;
}
