#include <stdio.h>

#include "headers/HashAberta.h"

#define HASH_LENGTH 5
#define HASH_CHARGE_FACTOR (float) 0.7

int menu() {
    int select = 0;

    printf("\n\n===== MENU =====");
    printf("\n1- Inserir");
    printf("\n2- Buscar");
    printf("\n3- Buscar e Imprimir");
    printf("\n4- Remover");
    printf("\n5- Limpar");
    printf("\n6- Imprimir");
    printf("\n7- Imprimir Bloco");
    printf("\n0- Sair");

    printf("\nESCOLHA: ");
    scanf(" %d", &select);
    printf("\n");

    return select;
}

int main() {
    HashAberta *hashAberta = newHashAberta("Hash Aberta", HASH_LENGTH, HASH_CHARGE_FACTOR);
    int continuar = 1;
    int index = 0;
    char *key = (char *) malloc(101 * sizeof(char));

    if (hashAberta == NULL) {
        printf("\n\tERRO DE ALOCAÇÃO");
        return 0;
    }

    while (continuar) {
        switch (menu()) {
            case 1:
                hashAberta = insertHash(hashAberta, readAluno());
                break;
            case 2:
                printf("\nEntrada: ");
                scanf(" %s", key);
                printAluno(searchHash(hashAberta, key));
                break;
            case 3:
                printf("\nEntrada: ");
                scanf(" %s", key);
                findAndPrintHash(hashAberta, key);
                break;
            case 4:
                printf("\nEntrada: ");
                scanf(" %s", key);
                removeHash(hashAberta, key);
                break;
            case 5:
                clearHash(hashAberta);
                break;
            case 6:
                printHash(hashAberta);
                break;
            case 7:
                printf("\nEntrada: ");
                scanf(" %d", &index);
                printBlock(hashAberta, index);
                break;
            case 0:
                free(hashAberta);
                continuar = 0;
                break;
        }
    }

    return 0;
}
