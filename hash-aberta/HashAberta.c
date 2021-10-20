#include "headers/HashAberta.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_INVALID_LENGTH "\n\tERRO: Não e possível criar uma HASH com menos de 1 índice!\n"

#define STATUS_APAGADO -1
#define STATUS_VAZIO 0
#define STATUS_OCUPADO 1

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int hashFunction(HashAberta *hash, char *key);

Node *newNode(int index);

Node *createNodeSequence(int length);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

Node *newNode(int index) {
    Node *node = (Node *) malloc(sizeof(Node));

    node->index = index;
    node->status = STATUS_VAZIO;
    node->value = NULL;
    node->next = NULL;

    return node;
}

Node *createNodeSequence(int length) {
    if (length < 1) {
        return NULL;
    }

    Node *first = newNode(0);
    Node *aux = first;

    for (int i = 1; i < length; ++i) {
        aux->next = newNode(i);
        aux = aux->next;
    }
    aux->next = first;

    return first;
}

int hashFunction(HashAberta *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

HashAberta *newHashAberta(char *label, int length, float chargeFactor) {
    HashAberta *hash = (HashAberta*) malloc(sizeof(HashAberta));

    hash->label = label;
    hash->length = length;
    hash->chargeFactor = chargeFactor;
    hash->size = 0;
    hash->node = createNodeSequence(hash->length);

    return hash;
}