#include <stdio.h>

#include "headers/HashFechada.h"
#include "headers/Aluno.h"

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

#define LINHAS_MATRIZ 5

int menu() {
    int choice = 0;

    printf("\n\n========== MENU ==========");
    printf("\n1- Inserir");
    printf("\n2- Imprimir");
    printf("\n3- Buscar");
    printf("\n4- Remover");
    printf("\n5- Limpar");
    printf("\n6- Clonar");
    printf("\n7- Estatística");
    printf("\n0- Sair");
    printf("\nESCOLHA: ");
    scanf("%d", &choice);

    return choice;
}

int main() {
    HashFechada *hash = newHashFechada("Hash", LINHAS_MATRIZ);
    HashFechada *clone = newHashFechada("Clone", LINHAS_MATRIZ);
    Aluno value;
    char key[16];
    int codition = 1;

    if(hash == NULL || clone == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        free(hash);
        free(clone);
        return 0;
    }

    while (codition) {
        switch (menu()) {
            case 1:
                printf("\nEntrada: ");
                value = readAluno();
                insertHash(hash, value);
                break;
            case 2:
                printHash(hash);
                printf("\n");
                printHash(clone);
                break;
            case 3:
                printf("\nEntrada: ");
                scanf(" %s", key);
                printf("\nSaída: ");
                printAluno(searchHash(hash, key));
                break;
            case 4:
                printf("\nEntrada: ");
                scanf(" %s", key);
                removeHash(hash, key);
                break;
            case 5:
                clearHash(hash);
                break;
            case 6:
                cloneHash(clone, hash);
                break;
            case 7:
                printStatisticHash(hash);
                break;
            case 0:
                codition = 0;
                break;
        }
    }

    free(hash);
    free(clone);

    return 0;
}
