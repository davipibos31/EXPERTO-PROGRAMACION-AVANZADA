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
 * @brief Función principal del programa
 * @return 0 si se ejecuta correctamente
 */
        int main (){
            
            menu(NAME_ARCHIVE);
            stop();
            return 0;
        }
        int cont = 0;

/**
 * @brief Muestra el menú principal y llama a las funciones correspondientes según la opción seleccionada
 * @param nameArchive Nombre del archivo donde se guardan los datos de los clientes
 */
        void menu(char *nameArchive)
        {
            
            int option;
            char namearchive[] = NAME_ARCHIVE;

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
                        createCliente(namearchive);
                        break;
                    case 2:
                        deleteCliente(namearchive);
                        break;
                    case 3:
                        showClientes(namearchive);
                        break;
                    case 4:
                        realizarViaje(namearchive);
                        break;
                    case 5:
                        quitarViaje(namearchive);
                        break;
                    case 0:
                        printf("Saliendo del programa...\n");
                        break;
                    default:
                        printf("Opción inválida\n");
                        break;
                }
            } while (option != 0);

            return 0;
    }
        
        
/**
 * @brief Crea un nuevo cliente solicitando los datos al usuario
 * @return Estructura Clientes con los datos del nuevo cliente
 */
        void createCliente(char *nameArchive) {
            FILE *file;
            Clientes *cliente = malloc(sizeof(Clientes));

            file = fopen(nameArchive, "a");

            if (!file) {
                printf("Error al abrir el archivo\n");
            } else {
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

                fwrite(cliente, sizeof(Clientes), 1, file);
                fclose(file);
                printf("Cliente creado!\n");
                
/**
 * @brief Guarda los datos de un cliente en el archivo especificado
 * @param clientes Estructura Clientes con los datos del cliente a guardar
 * @param nameArchive Nombre del archivo donde se guardarán los datos
 */
                
                FILE *file;
    
                file = fopen(nameArchive, "a");
    
                if (!file) {
                    printf("Error al abrir el archivo\n");
                } else {
                    fwrite(&cliente, sizeof(Clientes), 1, file);
                    fclose(file);
                    printf("Cliente guardado!\n");
                    stop();
            }   
                stop();
            }

        free(cliente);
    }



/**
 * @brief Elimina un cliente del archivo especificado
 * @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
 */
        void deleteCliente(char *nameArchive)
        {
            system("cls");
            FILE *file, *fileAux;
            Clientes clientes;
            
            fileAux=fopen(NAME_ARCHIVE_AUX,"w");
            file=fopen(nameArchive,"r");

            if(!file){
                printf("Empty\n");
            }
            else{

                char dni[20];
                printf("DNI/nombre del cliente para eliminar:\n");
                fflush(stdin);
                gets(dni);
                //Recibe los mismo parametros que fwrite
                while(fread(&clientes, sizeof(Clientes),1, file)){

                    if (!strcmp(clientes.dni,dni))
                    {
                        //fwrite(&clientes, sizeof(Clientes),1, fileAux);
                    }
                    if (strcmp(clientes.dni,dni))
                    {
                        fwrite(&clientes, sizeof(Clientes),1, fileAux);
                    }
                    
                }
                fclose(fileAux); 
                fclose(file);
                fileAux=fopen(NAME_ARCHIVE_AUX,"r");
                file=fopen(nameArchive,"w");
                while(fread(&clientes, sizeof(Clientes),1, fileAux)){

                    fwrite(&clientes, sizeof(Clientes),1, file);
                }

            }

            stop();
            fclose(file);
            fclose(fileAux);
            remove(fileAux);
        }
        
/**
 * @brief Muestra los clientes almacenados en el archivo especificado
 * @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
 */
        void showClientes(char *nameArchive) {
            FILE *file;
            Clientes clientes;
            file = fopen(nameArchive, "r");

            if (!file) {
                printf("Error al abrir el archivo\n");
            } else {
            while (fread(&clientes, sizeof(Clientes), 1, file)) {
            printf("DNI: %s\n", clientes.dni);
            printf("Nombre: %s\n", clientes.nombre);
            printf("Dirección: %s\n", clientes.direccion);
            printf("Viajes: %d\n", clientes.viajes);
            printf("-------------------------\n");
            }

            fclose(file);
            stop();
            }
        }


/**
 * @brief Realiza un viaje para un cliente especificado
 * @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
 */
        void realizarViaje(char *nameArchive) {
            FILE *file, *fileAux;
            Clientes clientes;
            char dni[20];
            file = fopen(nameArchive, "r");
            fileAux = fopen(NAME_ARCHIVE_AUX, "w");

            if (!file || !fileAux) {
                printf("Error al abrir el archivo\n");
            } else {
                printf("DNI del cliente que realiza el viaje: ");
            fflush(stdin);
            gets(dni);

            while (fread(&clientes, sizeof(Clientes), 1, file)) {
                if (strcmp(clientes.dni, dni) == 0) {
                    clientes.viajes++;
                }
                fwrite(&clientes, sizeof(Clientes), 1, fileAux);
            }

            fclose(file);
            fclose(fileAux);
            remove(nameArchive);
            rename(NAME_ARCHIVE_AUX, nameArchive);
            printf("Viaje registrado!\n");
            stop();
            }
        }


/**
 * @brief Quita un viaje para un cliente especificado
 * @param nameArchive Nombre del archivo donde se encuentran los datos de los clientes
 */
        void quitarViaje(char *nameArchive) {
            FILE *file, *fileAux;
            Clientes clientes;
            char dni[20];
            file = fopen(nameArchive, "r");
            fileAux = fopen(NAME_ARCHIVE_AUX, "w");

            if (!file || !fileAux) {
                printf("Error al abrir el archivo\n");
            } else {
                printf("DNI del cliente al que se le quita el viaje: ");
                fflush(stdin);
                gets(dni);

                while (fread(&clientes, sizeof(Clientes), 1, file)) {
                    if (strcmp(clientes.dni, dni) == 0) {
                        if (clientes.viajes > 0) {
                            clientes.viajes--;
                        } else {
                            printf("El cliente no tiene viajes registrados\n");
                        }
                    }
                    fwrite(&clientes, sizeof(Clientes), 1, fileAux);
                }

                fclose(file);
                fclose(fileAux);
                remove(nameArchive);
                rename(NAME_ARCHIVE_AUX, nameArchive);
                printf("Viaje quitado!\n");
                stop();
            }
        }

/**
 * @brief Parada del programa 
 */
        void stop() {
            printf("\nPulsa Enter para continuar...");
            fflush(stdin);
            getchar();
        }
        char ninguna[10] = {'N', 'i', 'n', 'g', 'u', 'n', 'a', '\0'};
        char alquiler[20] = {'A', 'l', 'q', 'u', 'i', 'l', 'e', 'r', ' ', 'V','e', 'h', 'i', 'c', 'u', 'l', 'o', '\0'};
        char tren[10] = {'T', 'r', 'e', 'n', '\0'};
        char avion[10] = {'A', 'v', 'i', 'o', 'n', '\0'};

/**
 * @brief Muestra el menú secundario y llama a las funciones correspondientes según la opción seleccionada
 */
        void menu2()
        {
            Clientes clientes;
            int op;
            do{
                system("cls");
                printf("[1]Ninguna\n");
                printf("[2]Aquiler Vehiculo\n");
                printf("[3]Tren\n");
                printf("[4]Avion\n");
                printf("[5]Exit\n");
                printf(" Inicia opcion: ");
                scanf("%i",&op);
            if(op>0 && op<6){
                system("cls");
                switch(op){
                    case 1:
                        strcpy( clientes.veh, ninguna );
                        printf( "El transporte es: %s.\n",clientes.veh );
                        clientes.veh;
                        stop();
                        break;
                    case 2:
                        strcpy( clientes.veh, alquiler );
                        printf( "El transporte es: %s.\n",clientes.veh );
                       clientes.veh;
                        stop();
                        break;
                    case 3:
                        strcpy( clientes.veh, tren );
                        printf( "El transporte es: %s.\n",clientes.veh );
                        clientes.veh;
                        stop();
                        break;
                    case 4:
                        strcpy( clientes.veh, avion );
                        printf( "El transporte es: %s.\n",clientes.veh );
                       // clientes.veh;
                        stop();
                        break;
                    case 5:
                        stop();
                    default:
                        printf("...\n");
                        stop();
                }
            }
            }while(op!=5);
        }
        