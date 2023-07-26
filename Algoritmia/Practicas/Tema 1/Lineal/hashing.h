#define LIBRE -1
#define BORRADO -2

typedef struct{
        char clave[510];
        char apellidos[255];
        char nombre[255];
        int edad;
        char goya[1];
        long cache;
} myreg;

void init(myreg t_hash[], int tam);
void insert(myreg r, myreg t_hash[], int tam);
int search(int v, myreg t_hash[], int tam);
int remove(int v, myreg t_hash[], int tam);
float loadfactor(myreg t_hash[], int tam);

void show(myreg t_hash[], int tam);
