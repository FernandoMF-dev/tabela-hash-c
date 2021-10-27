#include <stdio.h>

#include "headers/HashAberta.h"
#include "headers/ControleArquivoAluno.h"

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
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
    HashAberta *hashAberta = newHashAberta("hash", HASH_LENGTH, HASH_CHARGE_FACTOR);
    int continuar = 1;
    char *key = (char *) malloc(101 * sizeof(char));

    if (hashAberta == NULL || key == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return 0;
    }

    hashAberta = readHashAlunoFromFile(hashAberta);

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
