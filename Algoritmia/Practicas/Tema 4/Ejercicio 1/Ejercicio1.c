#include <stdio.h>
#include <string.h>

void busquedaDirecta(char *texto, char *patron) {
    int i, j, k;
    int texto_len = strlen(texto);
    int patron_len = strlen(patron);

    for (i = 0; i <= texto_len - patron_len; i++) {
        j = 0;
        while (j < patron_len && texto[i + j] == patron[j]) {
            j++;
        }

        if (j == patron_len) {
            printf("Se encontró el patrón en la posición %d\n", i);
        }
    }
}

int main() {
    char texto[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
    char patron[] = "ipsum";

    busquedaDirecta(texto, patron);

    return 0;
}
