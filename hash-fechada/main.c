#include <stdio.h>

#include "headers/HashFechada.h"
#include "headers/ControleArquivoAluno.h"

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

#define LINHAS_MATRIZ_A 997
#define LINHAS_MATRIZ_B 1000

int menu() {
    int choice = 0;

    printf("\n\n========== MENU ==========");
    printf("\n1- Inserir");
    printf("\n2- Imprimir");
    printf("\n3- Buscar");
    printf("\n4- Remover");
    printf("\n5- Limpar");
    printf("\n6- Estatística");
    printf("\n0- Sair");
    printf("\nESCOLHA: ");
    scanf("%d", &choice);

    return choice;
}

int main() {
    HashFechada *hashA = newHashFechada("Hash997", LINHAS_MATRIZ_A);
    HashFechada *hashB = newHashFechada("Hash1000", LINHAS_MATRIZ_B);
    Aluno value;
    char key[16];
    int codition = 1;

    if(hashA == NULL || hashB == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        free(hashA);
        free(hashB);
        return 0;
    }

    readHashAlunoFromFile2(hashA, hashB);

    while (codition) {
        switch (menu()) {
            case 1:
                printf("\nEntrada: ");
                value = readAluno();
                insertHash(hashA, value);
                insertHash(hashB, value);
                break;
            case 2:
                printHash(hashA);
                printf("\n");
                printHash(hashB);
                break;
            case 3:
                printf("\nEntrada: ");
                scanf(" %s", key);
                printf("\nSaída: ");
                printAluno(searchHash(hashA, key));
                break;
            case 4:
                printf("\nEntrada: ");
                scanf(" %s", key);
                removeHash(hashA, key);
                removeHash(hashB, key);
                break;
            case 5:
                clearHash(hashA);
                break;
            case 6:
                printStatisticHash(hashA);
                printf("\n");
                printStatisticHash(hashB);
                break;
            case 0:
                writeHashOnFile(hashA);
                writeHashOnFile(hashB);
                codition = 0;
                break;
        }
    }

    free(hashA);
    free(hashB);

    return 0;
}
