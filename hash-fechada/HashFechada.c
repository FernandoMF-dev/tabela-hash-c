#include "headers/HashFechada.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define MAX_LIST_LABEL_LENGTH 7

// =-=-=-=-= METODOS PRIVADOS =-=-=-=-=

int hashFunction(HashFechada *hash, int key) {
    return key % hash->length;
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

void insertHash(HashFechada *hash, int value) {
    int index = hashFunction(hash, value);
    insertList(hash->elements[index], value);
}

int searchHash(HashFechada *hash, int key) {
    int index = hashFunction(hash, key);
    return searchList(hash->elements[index], key);
}

void removeHash(HashFechada *hash, int key) {
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