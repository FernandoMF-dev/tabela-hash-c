#include "headers/Node.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Inicializa e retorna uma nova intância de Node
 * */
Node *newNode(Aluno *value) {
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    node->value = value;
    node->next = NULL;

    return node;
}

/*
 * Imprime uma struct Node
 * */
void printNode(Node *node) {
    printAluno(node->value);
}

/*
 * Compara se uma chave (key) corresponde ao valor de um Node.
 *
 * Se sim, retorna 0.
 * Se a chave for menor, retorna -1.
 * Se a chave for maior, retorna 1.
 * Se Node for NULL, retorna 2.
 * */
int compareNodeByKey(Node *node, char *key) {
    if (node == NULL) {
        return 2;
    }

    Aluno *element = node->value;

    if (compareAlunoByKey(element, key) < 0) {
        return -1;
    }
    if (compareAlunoByKey(element, key) > 0) {
        return 1;
    }
    return 0;
}