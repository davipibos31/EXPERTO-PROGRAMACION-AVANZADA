/**
 * @file
 * @brief Agenda
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "libreria.h"

#define NAME_ARCHIVE "clientes.txt"
#define NAME_ARCHIVE_AUX "clientes_aux.txt"

/**
 * @brief Estructura de un cliente
 */
typedef struct {
    char dni[20];
    char nombre[50];
    char direccion[100];
    int viajes;
    struct ClienteNode* next;
} Cliente;

/**
 * @brief Estructura de un nodo de la pila de clientes
 */
typedef struct ClienteNode {
    Cliente* cliente;
    struct ClienteNode* next;
} ClienteNode;

ClienteNode* clienteStack = NULL; // Pila de clientes globales

/**
 * @brief Función principal del programa
 * @return 0 si se ejecuta correctamente
 */
int main() {
    menu(NAME_ARCHIVE);
    stop();
    return 0;
}

/**
 * @brief Muestra el menú principal y llama a las funciones correspondientes según la opción seleccionada
 * @param nameArchive Nombre del archivo donde se guardan los datos de los clientes
 */
void menu(char* nameArchive) {
    int option;

    do {
        printf("1. Crear cliente\n");
        printf("2. Eliminar cliente\n");
        printf("3. Mostrar clientes\n");
        printf("4. Realizar viaje\n");
        printf("5. Quitar viaje\n");
        printf("0. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%i", &option);

        switch (option) {
            case 1:
                createCliente(nameArchive);
                break;
            case 2:
                deleteCliente(nameArchive);
                break;
            case 3:
                showClientes(nameArchive);
                break;
            case 4:
                realizarViaje(nameArchive);
                break;
            case 5:
                quitarViaje(nameArchive);
                break;
            case 0:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida\n");
                break;
        }
    } while (option != 0);
}

/**
 * @brief Crea un nuevo cliente solicitando los datos al usuario y lo agrega a la pila de clientes
 * @param nameArchive Nombre del archivo donde se guardarán los datos de los clientes
 */
void createCliente(char* nameArchive) {
    Cliente* cliente = malloc(sizeof(Cliente));

    printf("Ingrese el DNI del cliente: ");
    fflush(stdin);
    gets(cliente->dni);

    printf("Ingrese el nombre del cliente: ");
    fflush(stdin);
    gets(cliente->nombre);

    printf("Ingrese la dirección del cliente: ");
    fflush(stdin);
    gets(cliente->direccion);

    printf("Ingrese la cantidad de viajes del cliente: ");
    scanf("%i", &(cliente->viajes));

    // Agregar el cliente a la pila
    ClienteNode* newNode = malloc(sizeof(ClienteNode));
    newNode->cliente = cliente;
    newNode->next = clienteStack;
    clienteStack = newNode;

    printf("Cliente creado!\n");
    stop();
}

/**
 * @brief Guarda los datos de la pila de clientes en el archivo especificado
 * @param nameArchive Nombre del archivo donde se guardarán los datos
 */
void saveClientesToFile(char* nameArchive) {
    FILE* file = fopen(nameArchive, "w");
    if (!file) {
        printf("Error al abrir el archivo\n");
    } else {
        ClienteNode* currentNode = clienteStack;
            while (currentNode != NULL) {
                Cliente* cliente = currentNode->cliente;
                fwrite(cliente, sizeof(Cliente), 1, file);
                currentNode = currentNode->next;
            }

        fclose(file);
        printf("Clientes guardados en el archivo!\n");
        stop();
    }
}

/**
 * @brief Elimina un cliente de la pila de clientes según el DNI especificado
 * @param dni DNI del cliente a eliminar
 */
void deleteClienteFromStack(char* dni) {
    if (clienteStack == NULL) {
        printf("La pila de clientes está vacía\n");
        stop();
        return;
    }

    ClienteNode* currentNode = clienteStack;
    ClienteNode* previousNode = NULL;

    while (currentNode != NULL) {
        if (strcmp(currentNode->cliente->dni, dni) == 0) {
            if (previousNode == NULL) {
                // El cliente a eliminar es el primer nodo de la pila
                clienteStack = currentNode->next;
            } else {
                previousNode->next = currentNode->next;
            }

            free(currentNode->cliente);
            free(currentNode);
            printf("Cliente eliminado de la pila de clientes!\n");
            stop();
            return;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    printf("Cliente no encontrado en la pila de clientes\n");
    stop();
}

/**

* @brief Elimina un cliente del archivo especificado y de la pila de clientes
*
* @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
*/
void deleteCliente(char* nameArchive) {
    FILE* file;
    Cliente cliente;
    ClienteNode* previousNode = NULL;
    ClienteNode* currentNode = clienteStack;

    char dni[20];
    printf("DNI del cliente para eliminar: ");
    fflush(stdin);
    gets(dni);

    while (currentNode != NULL) {
        Cliente* currentCliente = currentNode->cliente;
        if (strcmp(currentCliente->dni, dni) == 0) {
            if (previousNode == NULL) {
                clienteStack = currentNode->next;
            } else {
                previousNode->next = currentNode->next;
            }
                free(currentCliente);
                free(currentNode);
                printf("Cliente eliminado!\n");
                stop();
                return;
            }
        previousNode = currentNode;
        currentNode = currentNode->next;

    }

    // Si el cliente no se encontró en la pila, buscarlo en el archivo
    file = fopen(nameArchive, "r");
    if (!file) {
        printf("Error al abrir el archivo\n");
        stop();
        return;
    }

    FILE* fileAux = fopen(NAME_ARCHIVE_AUX, "w");
    if (!fileAux) {
        printf("Error al abrir el archivo auxiliar\n");
        fclose(file);
        stop();
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (strcmp(cliente.dni, dni) != 0) {
            fwrite(&cliente, sizeof(Cliente), 1, fileAux);
        }
    }

    fclose(file);
    fclose(fileAux);
    remove(nameArchive);
    rename(NAME_ARCHIVE_AUX, nameArchive);
    printf("Cliente eliminado del archivo!\n");
    stop();
}

/**

* @brief Muestra los clientes almacenados en el archivo especificado y en la pila de clientes
*
* @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
*/
void showClientes(char* nameArchive) {
    FILE* file;
    Cliente cliente;
    int count = 0;

    printf("--- Clientes en la pila ---\n");
    ClienteNode* currentNode = clienteStack;
    while (currentNode != NULL) {
        Cliente* currentCliente = currentNode->cliente;
        printf("Cliente %d:\n", count + 1);
        printf("DNI: %s\n", currentCliente->dni);
        printf("Nombre: %s\n", currentCliente->nombre);
        printf("Dirección: %s\n", currentCliente->direccion);
        printf("Viajes: %d\n", currentCliente->viajes);
        printf("-------------------------\n");
        currentNode = currentNode->next;
        count++;
    }
    file = fopen(nameArchive, "r");
    if (!file) {
        printf("Error al abrir el archivo\n");
        stop();
        return;
    }

    printf("--- Clientes en el archivo ---\n");
    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        printf("Cliente %d:\n", count + 1);
        printf("DNI: %s\n", cliente.dni);
        printf("Nombre: %s\n", cliente.nombre);
        printf("Dirección: %s\n", cliente.direccion);
        printf("Viajes: %d\n", cliente.viajes);
        printf("-------------------------\n");
        count++;
    }

    fclose(file);
    stop();
}

/**

* @brief Realiza un viaje para un cliente especificado y actualiza la pila de clientes y el archivo
*
* @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
*/
void realizarViaje(char* nameArchive) {
    FILE* file;
    Cliente cliente;
    char dni[20];

    printf("DNI del cliente que realiza el viaje: ");
    fflush(stdin);
    gets(dni);

    ClienteNode* currentNode = clienteStack;
    while (currentNode != NULL) {
        Cliente* currentCliente = currentNode->cliente;
        if (strcmp(currentCliente->dni, dni) == 0) {
            currentCliente->viajes++;
            printf("Viaje registrado para el cliente en la pila!\n");
            stop();
            return;
        }
    currentNode = currentNode->next;
    }

    file = fopen(nameArchive, "r+");
    if (!file) {
        printf("Error al abrir el archivo\n");
        stop();
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (strcmp(cliente.dni, dni) == 0) {
            cliente.viajes++;
            fseek(file, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, file);
            printf("Viaje registrado para el cliente en el archivo!\n");
            stop();
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Cliente no encontrado\n");
    stop();
}

/**
*
* @brief Quita un viaje para un cliente especificado y actualiza la pila de clientes y el archivo
*
* @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
*/
void quitarViaje(char* nameArchive) {
    FILE* file;
    Cliente cliente;
    char dni[20];

    printf("DNI del cliente al que se le quita el viaje: ");
    fflush(stdin);
    gets(dni);

    ClienteNode* currentNode = clienteStack;
    while (currentNode != NULL) {
        Cliente* currentCliente = currentNode->cliente;
        if (strcmp(currentCliente->dni, dni) == 0) {
            if (currentCliente->viajes > 0) {
                currentCliente->viajes--;
                printf("Viaje quitado para el cliente en la pila!\n");
            } else {
                printf("El cliente no tiene viajes registrados\n");
            }
            stop();
            return;
        }
        currentNode = currentNode->next;
    }

    file = fopen(nameArchive, "r+");
    if (!file) {
        printf("Error al abrir el archivo\n");
        stop();
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (strcmp(cliente.dni, dni) == 0) {
            if (cliente.viajes > 0) {
                cliente.viajes--;
                fseek(file, -sizeof(Cliente), SEEK_CUR);
                fwrite(&cliente, sizeof(Cliente), 1, file);
                printf("Viaje quitado para el cliente en el archivo!\n");
                stop();
                fclose(file);
                return;
            } else {
                printf("El cliente no tiene viajes registrados\n");
                stop();
                fclose(file);
                return;
            }
        }
    }
    fclose(file);
    printf("Cliente no encontrado\n");
    stop();
}

/**
*
* @brief Guarda los datos de la pila de clientes en un archivo de texto
*
* @param nameArchive Nombre del archivo donde se guardarán los datos
*/
void guardarPilaEnArchivo(char* nameArchive) {
    FILE* file;
    file = fopen(nameArchive, "w");
    if (!file) {
        printf("Error al abrir el archivo\n");
        stop();
        return;
    }

    ClienteNode* currentNode = clienteStack;
    while (currentNode != NULL) {
        Cliente* cliente = currentNode->cliente;
        fwrite(cliente, sizeof(Cliente), 1, file);
        currentNode = currentNode->next;
    }

    fclose(file);
    printf("Pila de clientes guardada en el archivo!\n");
    stop();
}

/**
*
* @brief Carga los datos de un archivo de texto en la pila de clientes
*
* @param nameArchive Nombre del archivo desde donde se cargarán los datos
*/
void cargarPilaDesdeArchivo(char* nameArchive) {
    FILE* file;
    Cliente cliente;
    file = fopen(nameArchive, "r");
    if (!file) {
        printf("Error al abrir el archivo\n");
        stop();
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        //pushCliente(cliente.dni, cliente.nombre, cliente.direccion, cliente.viajes);
    }

    fclose(file);
    printf("Pila de clientes cargada desde el archivo!\n");
    stop();
}
/**
 * @brief Parada del programa 
 */
        void stop() {
            printf("\nPulsa Enter para continuar...");
            fflush(stdin);
            getchar();
        }