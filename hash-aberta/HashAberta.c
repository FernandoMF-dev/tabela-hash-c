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

int compareNodeByKey(Node *node, char *key);

Node *newNode(int index);

Node **createNodeSequence(int length);

HashAberta *expandsHash(HashAberta *base);

int regulateBlockIndex(HashAberta *base, int block);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

int hashFunction(HashAberta *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

int compareNodeByKey(Node *node, char *key) {
    return node->status == STATUS_OCUPADO && compareAlunoByKey(node->value, key) == 0;
}

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

HashAberta *expandsHash(HashAberta *base) {
    HashAberta *hash = newHashAberta(base->label, hash->length * EXPANSAO_MULTIPLICADOR, hash->chargeFactor);

    cloneHash(hash, base);

    free(base->elements);
    free(base);
    return hash;
}

int regulateBlockIndex(HashAberta *base, int block) {
    while (block > base->length - 1) {
        block -= base->length;
    }
    while (block < 0) {
        block += base->length;
    }

    return block;
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
        if (compareNodeByKey(node, key)) {
            return node->value;
        }
        node = node->next;
    }
    printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    return NULL;
}

void removeHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];

    while (node->status != STATUS_VAZIO) {
        if (compareNodeByKey(node, key)) {
            node->status = STATUS_APAGADO;
            free(node->value);
            hash->size--;
            return;
        }
        node = node->next;
    }
    printf(ERROR_REGISTRO_NAO_ENCONTRADO);
}

void clearHash(HashAberta *hash) {
    Node *node = hash->elements[0];

    do {
        if (node->status != STATUS_VAZIO) {
            node->status = STATUS_VAZIO;
            free(node->value);
        }
        node = node->next;
    } while (node->index != 0);
    hash->size = 0;
}

void cloneHash(HashAberta *target, HashAberta *source) {
    Node *node = source->elements[0];

    do {
        if (node->status == STATUS_OCUPADO) {
            insertHash(target, node->value);
        }
        node = node->next;
    } while (node->index != 0);
}

void printHash(HashAberta *hash) {
    int contador = 0;

    printf("[ ");
    for (int i = 0; i < hash->length; ++i) {
        if (hash->elements[i]->status == STATUS_OCUPADO) {
            printAluno(hash->elements[i]->value);
            contador++;
            if (contador < hash->size) {
                printf(", ");
            }
        }
    }
    printf(" ]");
}

void printBlock(HashAberta *hash, int block) {
    block = regulateBlockIndex(hash, block);
    Node *node = hash->elements[block];
    int alreadyPrinted = 0;

    printf("[ ");
    while (node->status != STATUS_VAZIO) {
        if (alreadyPrinted) {
            printf(", ");
        }

        if (node->status == STATUS_OCUPADO) {
            printAluno(node->value);
        } else {
            printf("{}");
        }

        alreadyPrinted = 1;
        node = node->next;
    }
    printf(" ]");
}