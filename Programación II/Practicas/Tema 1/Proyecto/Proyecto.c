//Agenda
        #include <stdio.h>
        #include <stdlib.h>
        #include <conio.h>
        #include <string.h>
        #define NAME_ARCHIVE "clientes.txt"
        #define NAME_ARCHIVE_AUX "clientes_aux.txt"
        
        //Clientes
        typedef struct clientes{
            char dni[20];
            char nombre[100];
            char direccion[150];
            int  viajes;
            int precio_alo;
            int precio_des;
            char ciu_des[20];
            int num_noche;
            char veh[20];
        }Clientes;

        //Funciones
        void menu(char *nameArchive);
        Clientes createCliente();
        void saveCliente(Clientes clientes, char *nameArchive);
        void showClientes(char *nameArchive);
        void deleteCliente(char *nameArchive);
        void realizarViaje(char *nameArchive);

        void menu2();
        void stop();

        int main (){
            
            menu(NAME_ARCHIVE);
            stop();
            return 0;
        }
        int cont = 0;
        void menu(char *nameArchive)
        {
            
            int op;
            do{
                system("cls");
                printf("[1]Crear Cliente\n");
                printf("[2]Mostrar Clientes\n");
                printf("[3]Eliminar Cliente\n");
                printf("[4]Realizar Viaje\n");
                printf("[5]Quitar Viaje\n");
                printf("[6]Exit\n");
                printf(" Inicia opcion: ");
                scanf("%i",&op);
            if(op>0 && op<7){
                system("cls");
                switch(op){
                    case 1:
                        if (cont >=0 && cont <=9) {
                            saveCliente(createCliente(),NAME_ARCHIVE);
                            cont++;
                        } else if (cont > 9) {
                            printf("Error: Alcanzado maximo de clientes\n");
                            stop();
                        }
                        break;
                    case 2:
                        showClientes(NAME_ARCHIVE);
                        break;
                    case 3:
                        deleteCliente(NAME_ARCHIVE);
                        break;
                    case 4:
                        realizarViaje(NAME_ARCHIVE);
                        break;
                    case 5:
                        quitarViaje(NAME_ARCHIVE);
                        break;
                    case 6:
                        exit(1);
                    default:
                        printf("Mala decisión...\n");
                        stop();
                }
            }
            }while(op!=6);
        }
        //Creando el cliente
        Clientes createCliente()
        {
            Clientes clientes;
            clientes.viajes = 0;
            clientes.num_noche = 0;
            clientes.precio_alo = 0;
            clientes.precio_des = 0;
            printf("DNI:\n");
            fflush(stdin);
            gets(clientes.dni);
            printf("Nombre:\n");
            fflush(stdin);
            gets(clientes.nombre);
            printf("Direccion:\n");
            fflush(stdin);
            gets(clientes.direccion);
            printf("Viajes: %i\n", clientes.viajes);
            fflush(stdin);
            gets(clientes.viajes);

            return clientes;
        }

        void saveCliente(Clientes clientes, char* nameArchive)
        {
            FILE* file;
            //si el archivo existe va a
            //agregar el nuevo cliente que creamos al final del archivo
            //no va a sobreescribir
            file=fopen(nameArchive,"a");

            if(!file){
                printf("Error\n");
                stop();
            }
            else{
                //Recibe 4 parametros:
                //1-Dirección de memoria de la variable que queremos guardar
                //2-El tamaño del tipo de dato
                //3-La cantidad de datos que queremos guardar
                //4-La variable del archivo
                fwrite(&clientes, sizeof(Clientes),1, file);
                printf("Cliente Guardado!\n");
                stop();
                fclose(file);
            }
        }

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
        //Mostrar contactos
        void showClientes(char *nameArchive)
        {
            FILE *file;
            file=fopen(nameArchive,"r");
            if(!file){
                printf("Empty\n");
                stop();
            }
            else{
                Clientes clientes;

                printf("\n\n%-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "DNI", "Nombre","Direccion", "Viajes", "precio alo", "precio desp", "transporte");
                //recibe los mismo parametros que fwrite
                while(fread(&clientes, sizeof(Clientes),1, file)){
                    printf("%-10s %-10s %-10s %-10i %-10i %-10i %-10s\n", clientes.dni, clientes.nombre,clientes.direccion, clientes.viajes, clientes.precio_alo, clientes.precio_des, clientes.veh);
                }
                fclose(file);
                printf("\n");
                stop();

            }
        }

        void realizarViaje(char *nameArchive)
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
                printf("DNI/nombre del cliente para hacer viaje:\n");
                fflush(stdin);
                gets(dni);
                //Recibe los mismo parametros que fwrite
                while(fread(&clientes, sizeof(Clientes),1, file)){

                    if (!strcmp(clientes.dni,dni))
                    {
                        menu2();
                        clientes.viajes++;
                        printf("\nID VIAJE: <%s>_<%i>_<16/04/23>\n", clientes.dni,clientes.viajes);
                        clientes.precio_alo = clientes.precio_alo+100;
                        clientes.precio_des = clientes.precio_des+180;
                        fwrite(&clientes, sizeof(Clientes),1, fileAux);
                        stop();
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
            
            printf("\nViaje realizado con exito!!!\n");
            stop();
            fclose(file);
            fclose(fileAux);
            remove(fileAux);
        }

        void quitarViaje(char *nameArchive)
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
                printf("DNI/nombre del cliente para quitar viaje:\n");
                fflush(stdin);
                gets(dni);
                //Recibe los mismo parametros que fwrite
                while(fread(&clientes, sizeof(Clientes),1, file)){

                    if (!strcmp(clientes.dni,dni))
                    {
                        if (clientes.viajes != 0) {
                            clientes.viajes--;
                            printf("\nID VIAJE: %s%i\n", clientes.dni,clientes.viajes);
                            
                            clientes.precio_alo = clientes.precio_alo-100;
                            clientes.precio_des = clientes.precio_des-180;
                            stop();
                        }
                        fwrite(&clientes, sizeof(Clientes),1, fileAux);
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
             
            printf("\nViaje quitado con exito!!!\n");
            stop();
            fclose(file);
            fclose(fileAux);
            remove(fileAux);
        }

        void stop()
        {
            printf("Press any key to continue...\n");
            getch();
        }
        char ninguna[10] = {'N', 'i', 'n', 'g', 'u', 'n', 'a', '\0'};
        char alquiler[20] = {'A', 'l', 'q', 'u', 'i', 'l', 'e', 'r', ' ', 'V','e', 'h', 'i', 'c', 'u', 'l', 'o', '\0'};
        char tren[10] = {'T', 'r', 'e', 'n', '\0'};
        char avion[10] = {'A', 'v', 'i', 'o', 'n', '\0'};
        
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
        