#include "headers/HashAberta.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"
#define ERROR_INVALID_LENGTH "\n\tERRO: Não e possível criar uma HASH com menos de 1 índice!\n"

#define EXPANSAO_MULTIPLICADOR 2
#define STATUS_APAGADO -1
#define STATUS_VAZIO 0
#define STATUS_OCUPADO 1

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int hashFunction(HashAberta *hash, char *key);

Node *newNode(int index);

Node **createNodeSequence(int length);

HashAberta *expandsHash(HashAberta *base);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

Node *newNode(int index) {
    Node *node = (Node *) malloc(sizeof(Node));

    node->index = index;
    node->status = STATUS_VAZIO;
    node->value = NULL;
    node->next = NULL;

    return node;
}

Node **createNodeSequence(int length) {
    if (length < 1) {
        return NULL;
    }

    Node **sequence = (Node **) malloc(length * sizeof(Node *));
    sequence[0] = newNode(0);
    Node *aux = sequence[0];

    for (int i = 1; i < length; ++i) {
        aux->next = newNode(i);
        sequence[i] = aux;
        aux = aux->next;
    }
    aux->next = sequence[0];

    return sequence;
}

int hashFunction(HashAberta *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

HashAberta *expandsHash(HashAberta *base) {
    HashAberta *hash = newHashAberta(base->label, hash->length * EXPANSAO_MULTIPLICADOR, hash->chargeFactor);
    Node *node = base->elements[0];

    do {
        if (node->status == STATUS_OCUPADO) {
            insertHash(hash, node->value);
        }
        node = node->next;
    } while (node->index != 0);

    free(base->elements);
    free(base);
    return hash;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

HashAberta *newHashAberta(char *label, int length, float chargeFactor) {
    HashAberta *hash = (HashAberta *) malloc(sizeof(HashAberta));

    hash->label = label;
    hash->length = length;
    hash->chargeFactor = chargeFactor;
    hash->size = 0;
    hash->elements = createNodeSequence(hash->length);

    return hash;
}

HashAberta *insertHash(HashAberta *hash, Aluno *value) {
    if ((float) hash->size / (float) hash->length > hash->chargeFactor) {
        hash = expandsHash(hash);
    }

    int index = hashFunction(hash, value->matricula);
    Node *node = hash->elements[index];

    while (node->status == STATUS_OCUPADO) {
        node = node->next;
    }

    node->status = STATUS_OCUPADO;
    node->value = value;
    hash->size++;

    return hash;
}

Aluno *searchHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];

    while (node->status != STATUS_VAZIO) {
        if (compareAlunoByKey(node->value, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    return NULL;
}