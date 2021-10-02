#include "headers/Node.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

Node *newNode(Aluno value) {
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    node->value = value;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

void printNode(Node *node) {
    printAluno(node->value);
}

int compareNodeByKey(Node *node, char *key) {
    if (node == NULL) {
        return 2;
    }

    Aluno element = node->value;

    if (compareAlunoByKey(element, key) < 0) {
        return -1;
    }
    if (compareAlunoByKey(element, key) > 0) {
        return 1;
    }
    return 0;
}