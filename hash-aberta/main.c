#include <stdio.h>

#include "headers/HashAberta.h"
#include "headers/ControleArquivoAluno.h"

#define HASH_LENGTH 100000
#define HASH_CHARGE_FACTOR 0.9

int menu() {
    int select = 0;

    printf("\n\n===== MENU =====");
    printf("\n1- Inserir");
    printf("\n2- Buscar");
    printf("\n3- Remover");
    printf("\n4- Estatísticas");
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

    if (hashAberta == NULL || key == NULL) {
        printf("\n\tERRO DE ALOCAÇÃO");
        return 0;
    }

    readHashAlunoFromFile(hashAberta);

    while (continuar) {
        switch (menu()) {
            case 1:
                hashAberta = insertHash(hashAberta, readAluno());
                break;
            case 2:
                printf("\nEntrada: ");
                scanf(" %s", key);
                findAndPrintHash(hashAberta, key);
                break;
            case 3:
                printf("\nEntrada: ");
                scanf(" %s", key);
                removeHash(hashAberta, key);
                break;
            case 4:
                printStatisticsHash(hashAberta);
                break;
            case 0:
                writeHashOnFile(hashAberta);
                free(hashAberta);
                continuar = 0;
                break;
        }
    }

    return 0;
}
