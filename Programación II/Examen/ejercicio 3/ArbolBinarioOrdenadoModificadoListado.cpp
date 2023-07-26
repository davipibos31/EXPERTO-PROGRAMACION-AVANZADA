#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo_arbol {
    char nif[10];
    char apellido[100];
    struct nodo_arbol* izq;
    struct nodo_arbol* der;
} NODO_ARBOL, *P_NODO_ARBOL;

P_NODO_ARBOL insertar(P_NODO_ARBOL arbol) {
    P_NODO_ARBOL p;
    p = (P_NODO_ARBOL)malloc(sizeof(struct nodo_arbol));
    p->izq = p->der = NULL;

    printf("Introduce el NIF: ");
    scanf("%s", p->nif);

    printf("Introduce el apellido: ");
    scanf("%s", p->apellido);

    return p;
}

int pertenece(P_NODO_ARBOL arbol, char* nif) {
    if (arbol == NULL)
        return 0;

    if (strcmp(arbol->nif, nif) == 0)
        return 1;

    if (strcmp(arbol->nif, nif) > 0)
        return pertenece(arbol->izq, nif);
    else
        return pertenece(arbol->der, nif);
}

P_NODO_ARBOL encontrar(P_NODO_ARBOL arbol, char* nif) {
    if (arbol == NULL)
        return NULL;

    if (strcmp(arbol->nif, nif) == 0)
        return arbol;

    if (strcmp(arbol->nif, nif) > 0)
        return encontrar(arbol->izq, nif);
    else
        return encontrar(arbol->der, nif);
}

P_NODO_ARBOL padre_de(P_NODO_ARBOL arbol, P_NODO_ARBOL nodo) {
    if (arbol == NULL)
        return NULL;

    if (arbol->izq == nodo || arbol->der == nodo)
        return arbol;
    else if (strcmp(arbol->nif, nodo->nif) > 0)
        return padre_de(arbol->izq, nodo);
    else
        return padre_de(arbol->der, nodo);
}

P_NODO_ARBOL eliminar(P_NODO_ARBOL a, char* nif) {
    P_NODO_ARBOL q, p;

    if (a == NULL)
        return a;

    if (strcmp(a->nif, nif) > 0)
        a->izq = eliminar(a->izq, nif);
    else if (strcmp(a->nif, nif) < 0)
        a->der = eliminar(a->der, nif);
    else {
        if ((a->der == NULL) && (a->izq == NULL)) {
            free(a);
            return NULL;
        }

        if (a->der == NULL) {
            q = a->izq;
            free(a);
            return q;
        }

        if (a->izq == NULL) {
            q = a->der;
            free(a);
            return q;
        }

        for (p = a, q = a->izq; q->der != NULL; q = q->der)
            p = q;

        if (p != a)
            p->der = q->izq;
        else
            p->izq = q->izq;

        strcpy(a->nif, q->nif);
        strcpy(a->apellido, q->apellido);
        free(q);
    }

    return a;
}

void orden_previo(P_NODO_ARBOL arbol) {
    if (arbol != NULL) {
        printf("\n%s %s", arbol->nif, arbol->apellido);
        orden_previo(arbol->izq);
        orden_previo(arbol->der);
    }
}

void orden_simetrico(P_NODO_ARBOL arbol) {
    if (arbol != NULL) {
        orden_simetrico(arbol->izq);
        printf("\n%s %s", arbol->nif, arbol->apellido);
        orden_simetrico(arbol->der);
    }
}

void orden_posterior(P_NODO_ARBOL arbol) {
    if (arbol != NULL) {
        orden_posterior(arbol->izq);
        orden_posterior(arbol->der);
        printf("\n%s %s", arbol->nif, arbol->apellido);
    }
}

int main(void) {
    int opcion, orden_opc;
    char aux[10];
    P_NODO_ARBOL a = NULL;

    do {
        printf("\n\n1.Insertar\n");
        printf("2.Pertenece\n");
        printf("3.Listar\n");
        printf("4.Padre de\n");
        printf("5.Borrar\n");
        printf("6.Recorridos\n");
        printf("7.Salir\n");
        printf("\nIntroduce una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                a = insertar(a);
                printf("\nElemento insertado");
                break;

            case 2:
                printf("\nNIF a buscar: ");
                scanf("%s", aux);
                if (pertenece(a, aux))
                    printf("\nPertenece");
                else
                    printf("\nNo pertenece");

                break;

            case 3:
                printf("\nNIF a encontrar: ");
                scanf("%s", aux);
                if (encontrar(a, aux) != NULL)
                    printf("\nElemento en nodo: %s %s", encontrar(a, aux)->nif, encontrar(a, aux)->apellido);
                else
                    printf("\nNo encontrado");

                break;

            case 4:
                printf("\nNIF padre de: ");
                scanf("%s", aux);
                if (padre_de(a, encontrar(a, aux)) != NULL)
                    printf("\nPadre: %s %s", padre_de(a, encontrar(a, aux))->nif, padre_de(a, encontrar(a, aux))->apellido);
                else
                    printf("\nNo tiene padre");

                break;

            case 5:
                printf("\nNIF a eliminar: ");
                scanf("%s", aux);
                a = eliminar(a, aux);
                printf("\nElemento eliminado");
                break;

            case 6:
                printf("\n1.Orden previo");
                printf("\n2.Orden simetrico");
                printf("\n3.Orden posterior");
                printf("\nIntroduce una opción: ");
                scanf("%d", &orden_opc);

                switch (orden_opc) {
                    case 1:
                        orden_previo(a);
                        break;

                    case 2:
                        orden_simetrico(a);
                        break;

                    case 3:
                        orden_posterior(a);
                        break;
                }
                break;
        }
    } while (opcion != 7);

    system("pause");
    return 0;
}