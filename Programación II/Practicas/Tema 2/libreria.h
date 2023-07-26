/**
 * @struct Clientes
 * @brief Estructura para almacenar información de los clientes
 */
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

void menu(char *nameArchive);
void createCliente(char *nameArchive);
void saveCliente(char *nameArchive, Clientes cliente);
void showClientes(char *nameArchive);
void deleteCliente(char *nameArchive);
void realizarViaje(char *nameArchive);

void menu2();
void stop();