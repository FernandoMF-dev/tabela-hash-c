#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"
#include "Aluno.h"

#ifndef HASH_FECHADA_HASHFECHADA_H
#define HASH_FECHADA_HASHFECHADA_H

typedef struct HashFechada {
    char *label;
    int length;
    List **elements;
} HashFechada;

HashFechada *newHashFechada(char *label, int length);

void insertHash(HashFechada *hash, Aluno value);

Aluno searchHash(HashFechada *hash, char *key);

void removeHash(HashFechada *hash, char *key);

void clearHash(HashFechada *hash);

void cloneHash(HashFechada *target, HashFechada *source);

void printHash(HashFechada *hash);

#endif //HASH_FECHADA_HASHFECHADA_H
