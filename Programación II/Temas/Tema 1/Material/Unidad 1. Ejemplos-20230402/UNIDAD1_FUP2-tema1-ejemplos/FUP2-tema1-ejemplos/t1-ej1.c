#include <stdio.h>
#include <stdlib.h>

#define LINE_MAX    200

int leer_int (void) {
    int d;
    char buf[LINE_MAX];

    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &d);

    return d;
}

int main()
{
    printf("Introduzca un valor entero: ");
    printf("El valor introducido es %d", leer_int());

    return 0;
}
