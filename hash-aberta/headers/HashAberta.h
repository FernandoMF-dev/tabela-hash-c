#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Aluno.h"

#ifndef HASH_ABERTA_HASHABERTA_H
#define HASH_ABERTA_HASHABERTA_H

typedef struct Node {
    int index;
    int status;
    Aluno *value;
    struct Node *next;
} Node;

typedef struct HashAberta {
    char *label;
    int length;
    int size;
    float chargeFactor;
    Node **elements;
} HashAberta;

HashAberta *newHashAberta(char *label, int length, float chargeFactor);

HashAberta *insertHash(HashAberta *hash, Aluno *value);

Aluno *searchHash(HashAberta *hash, char *key);

void findAndPrintHash(HashAberta *hash, char *key);

void removeHash(HashAberta *hash, char *key);

void clearHash(HashAberta *hash);

void cloneHash(HashAberta *target, HashAberta *source);

void printHash(HashAberta *hash);

int sizeHash(HashAberta *hash);

void printBlock(HashAberta *hash, int block);

double averageNodesPerBlockHash(HashAberta *hash);

int shortestBlockHash(HashAberta *hash);

int longestBlockHash(HashAberta *hash);

void printStatisticHash(HashAberta *hash);

#endif //HASH_ABERTA_HASHABERTA_H
