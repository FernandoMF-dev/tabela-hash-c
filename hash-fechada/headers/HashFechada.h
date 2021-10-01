#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

#ifndef HASH_FECHADA_HASHFECHADA_H
#define HASH_FECHADA_HASHFECHADA_H

typedef struct HashFechada {
    char *label;
    int length;
    List **elements;
} HashFechada;

HashFechada *newHashFechada(char *label, int length);

void insertHash(HashFechada *hash, int value);

int searchHash(HashFechada *hash, int key);

void removeHash(HashFechada *hash, int key);

void clearHash(HashFechada *hash);

void cloneHash(HashFechada *target, HashFechada *source);

void printHash(HashFechada *hash);

#endif //HASH_FECHADA_HASHFECHADA_H
