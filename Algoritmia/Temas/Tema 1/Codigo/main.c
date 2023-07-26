#include "hashing.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM 10

int main(int argc, char *argv[])
{
    myreg myhash[TAM];
    myreg reg1, reg2, reg3;
    
    reg1.key = 10;
    reg2.key = 20;
    reg3.key = 11;
    
    
    
    init(myhash, TAM);
    insert(reg1, myhash, TAM);
    insert(reg2, myhash, TAM);
    insert(reg3, myhash, TAM);
    
    show(myhash, TAM);
    
    remove(10, myhash, TAM);

    show(myhash, TAM);
    
    int pos = search(11, myhash, TAM);
    printf("El valor 11 esta en la pos %d de la tabla\n",pos);
    
     
    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}