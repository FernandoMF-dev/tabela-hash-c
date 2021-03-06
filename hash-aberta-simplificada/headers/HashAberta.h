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
    double chargeFactor;
    Node **elements;
} HashAberta;

HashAberta *newHashAberta(char *label, int length, double chargeFactor);

HashAberta *insertHash(HashAberta *hash, Aluno *value);

Aluno *searchHash(HashAberta *hash, char *key);

void findAndPrintHash(HashAberta *hash, char *key);

void removeHash(HashAberta *hash, char *key);

void clearHash(HashAberta *hash);

void cloneHash(HashAberta *target, HashAberta *source);

void printHash(HashAberta *hash);

void printBlockHash(HashAberta *hash, int block);

int blockLengthHash(HashAberta *hash, int block);

int numberOfBlocksHash(HashAberta *hash);

double averageBlockLengthHash(HashAberta *hash);

int shortestBlockHash(HashAberta *hash);

int longestBlockHash(HashAberta *hash);

void printStatisticsHash(HashAberta *hash);

#endif //HASH_ABERTA_HASHABERTA_H
