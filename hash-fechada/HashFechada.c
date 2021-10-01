#include "headers/HashFechada.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define MAX_LIST_LABEL_LENGTH 7

// =-=-=-=-= METODOS PRIVADOS =-=-=-=-=

int hashFunction(HashFechada *hash, char *key) {
    int keyIntValue = (int) strtol(key, (char **) NULL, 10);
    return keyIntValue % hash->length;
}

List *initializeElementList(int i) {
    List *list = newList("");
    list->label = (char *) malloc((MAX_LIST_LABEL_LENGTH + 1) * sizeof(char));
    sprintf(list->label, "%d", i);

    return list;
}

List **initializeElements(int length) {
    List **elements = (List **) malloc(length * sizeof(List *));

    for (int i = 0; i < length; i++) {
        elements[i] = initializeElementList(i);
    }

    return elements;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

HashFechada *newHashFechada(char *label, int length) {
    HashFechada *hash = (HashFechada *) malloc(sizeof(HashFechada));

    hash->label = label;
    hash->length = length;
    hash->elements = initializeElements(length);

    return hash;
}

void insertHash(HashFechada *hash, Aluno value) {
    int index = hashFunction(hash, value.matricula);
    insertList(hash->elements[index], value);
}

Aluno searchHash(HashFechada *hash, char *key) {
    int index = hashFunction(hash, key);
    return searchList(hash->elements[index], key);
}

void removeHash(HashFechada *hash, char *key) {
    int index = hashFunction(hash, key);
    removeList(hash->elements[index], key);
}

void clearHash(HashFechada *hash) {
    for (int i = 0; i < hash->length; i++) {
        clearList(hash->elements[i]);
    }
}

void cloneHash(HashFechada *target, HashFechada *source) {
    clearHash(target);
    free(target->elements);
    target->length = source->length;
    target->elements = initializeElements(target->length);
    for (int i = 0; i < target->length; i++) {
        cloneList(target->elements[i], source->elements[i]);
    }
}

void printHash(HashFechada *hash) {
    if (strlen(hash->label)) {
        printf("\n%s:", hash->label);
    }
    for (int i = 0; i < hash->length; i++) {
        printList(hash->elements[i]);
    }
}

int sizeHash(HashFechada *hash) {
    int size = 0;

    for (int i = 0; i < hash->length; i++) {
        size += hash->elements[i]->size;
    }

    return size;
}

double averageNodesPerListHash(HashFechada *hash) {
    return (double) sizeHash(hash) / (double) hash->length;
}

int shortestListHash(HashFechada *hash) {
    int size = hash->elements[0]->size;
    int index = 0;

    for (int i = 1; i < hash->length; i++) {
        if (hash->elements[i]->size < size) {
            size = hash->elements[i]->size;
            index = i;
        }
    }

    return index;
}

int longestListHash(HashFechada *hash) {
    int size = hash->elements[0]->size;
    int index = 0;

    for (int i = 1; i < hash->length; i++) {
        if (hash->elements[i]->size > size) {
            size = hash->elements[i]->size;
            index = i;
        }
    }

    return index;
}

double standardDeviationHash(HashFechada *hash) {
    double standardDeviation = 0;
    double average = averageNodesPerListHash(hash);

    for (int i = 0; i < hash->length; i++) {
        standardDeviation += pow((double) (hash->elements[i]->size - average), 2);
    }

    return pow(standardDeviation / 2, 0.5);
}

int countListsNormalDistribution(HashFechada *hash) {
    double average = averageNodesPerListHash(hash);
    double standardDeviation = standardDeviationHash(hash);
    double size;
    int count = 0;

    for (int i = 0; i < hash->length; i++) {
        size = (double) hash->elements[i]->size;
        if (size < (average - standardDeviation) || size > (average + standardDeviation)) {
            count++;
        }
    }

    return count;
}

void printStatisticHash(HashFechada *hash) {
    int longestIndex = longestListHash(hash);
    int shortestIndex = shortestListHash(hash);

    if (strlen(hash->label)) {
        printf("\n%s:", hash->label);
    }
    printf("\nQuantidade total de elementos: %d", sizeHash(hash));
    printf("\nMédia de elementos por índice: %.2lf", averageNodesPerListHash(hash));
    printf("\nÍndice com o maior número de elementos(%d): %d", hash->elements[longestIndex]->size, longestIndex);
    printf("\nÍndice com o menor número de elementos(%d): %d", hash->elements[shortestIndex]->size, shortestIndex);
    printf("\nDesvio padrão da quantidade de elementos pelos índices: %.2lf", standardDeviationHash(hash));
    printf("\nQuantidade dentro do intervalo da média +/- o desvio padrão: %d", countListsNormalDistribution(hash));
}