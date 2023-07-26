#define LIBRE -1
#define BORRADO -2

typedef struct myreg{
        int key;
} myreg;

void init(myreg t_hash[], int tam);
void insert(myreg r, myreg t_hash[], int tam);
int search(int v, myreg t_hash[], int tam);
int remove(int v, myreg t_hash[], int tam);
float loadfactor(myreg t_hash[], int tam);

void show(myreg t_hash[], int tam);
