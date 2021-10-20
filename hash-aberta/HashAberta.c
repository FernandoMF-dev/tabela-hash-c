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

HashAberta *expandsHash(HashAberta *source);

int regulateHashIndex(HashAberta *base, int index);

int verifyContinueSearch(Node *node, int counter, int hashLength);

int findInitialShortestBlockIndex(HashAberta *hash);

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
    Node *aux;

    for (int i = 1; i < length; ++i) {
        aux = newNode(i);
        sequence[i - 1]->next = aux;
        sequence[i] = aux;
    }
    sequence[length - 1]->next = sequence[0];

    return sequence;
}

HashAberta *expandsHash(HashAberta *source) {
    HashAberta *target = newHashAberta(source->label, source->length * EXPANSAO_MULTIPLICADOR, source->chargeFactor);

    cloneHash(target, source);

    free(source->elements);
    free(source);
    return target;
}

int regulateHashIndex(HashAberta *base, int index) {
    while (index > base->length - 1) {
        index -= base->length;
    }
    while (index < 0) {
        index += base->length;
    }

    return index;
}

int verifyContinueSearch(Node *node, int counter, int hashLength) {
    return node->status != STATUS_VAZIO && counter < hashLength;
}

int findInitialShortestBlockIndex(HashAberta *hash) {
    int index = 0;

    while (hash->elements[regulateHashIndex(hash, index - 1)]->status != STATUS_VAZIO && index < hash->length) {
        index++;
    }

    return index;
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
    int counter = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        if (compareNodeByKey(node, key)) {
            return node->value;
        }
        node = node->next;
        counter++;
    }
    printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    return NULL;
}

void findAndPrintHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];
    int counter = 0;
    int found = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        if (compareNodeByKey(node, key)) {
            found = 1;
            break;
        }
        node = node->next;
        counter++;
    }

    if (found) {
        printf("\nO registro foi encontrado no índice %d\n", node->index);
        printAluno(node->value);
    } else {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    }
    printf("\nForam comparados %d registros antes de encontrar esse resultado", counter);
}

void removeHash(HashAberta *hash, char *key) {
    int index = hashFunction(hash, key);
    Node *node = hash->elements[index];
    int counter = 0;

    while (verifyContinueSearch(node, counter, hash->length)) {
        if (compareNodeByKey(node, key)) {
            node->status = STATUS_APAGADO;
            free(node->value);
            hash->size--;
            return;
        }
        node = node->next;
        counter++;
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
    int counter = 0;

    printf("%s(%d/%d)[ ", hash->label, hash->size, hash->length);
    for (int i = 0; i < hash->length; ++i) {
        if (hash->elements[i]->status == STATUS_OCUPADO) {
            printAluno(hash->elements[i]->value);
            counter++;
            if (counter >= hash->size) {
                break;
            }
            printf(", ");
        }
    }
    printf(" ]");
}

void printBlock(HashAberta *hash, int block) {
    block = regulateHashIndex(hash, block);
    Node *node = hash->elements[block];
    int alreadyPrinted = 0;

    printf("(%d)[ ", getBlockLength(hash, block));
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

int getBlockLength(HashAberta *hash, int block) {
    block = regulateHashIndex(hash, block);
    Node *node = hash->elements[block];
    int length = 0;

    while (node->status != STATUS_VAZIO) {
        length++;
        node = node->next;
    }

    return length;
}

int shortestBlockHash(HashAberta *hash) {
    int initialIndex = findInitialShortestBlockIndex(hash);
    int shortestIndex = initialIndex;
    int shortestLength = getBlockLength(hash, shortestIndex);
    int index = shortestLength + initialIndex + 1;
    int length;

    while (index < hash->length + initialIndex) {
        length = getBlockLength(hash, index);
        if (shortestLength == 0 || (length > 0 && length < shortestLength)) {
            shortestLength = length;
            shortestIndex = index;
        }
        index += length + 1;
    }

    return shortestIndex;
}

int longestBlockHash(HashAberta *hash) {
    int longestIndex = 0;
    int longestLength = getBlockLength(hash, longestIndex);
    int index = longestLength + 1;
    int length;

    while (index < hash->length) {
        length = getBlockLength(hash, index);
        if (length > longestLength) {
            longestLength = length;
            longestIndex = index;
        }
        index += length + 1;
    }

    return longestIndex;
}