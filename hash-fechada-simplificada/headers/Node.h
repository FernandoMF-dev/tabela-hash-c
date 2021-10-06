#include <stdio.h>
#include <stdlib.h>

#include "Aluno.h"

#ifndef HASH_FECHADA_NODE_H
#define HASH_FECHADA_NODE_H

typedef struct Node {
    struct Node *next;
    Aluno *value;
} Node;

Node *newNode(Aluno *value);

void printNode(Node *node);

int compareNodeByKey(Node *node, char *key);

#endif //HASH_FECHADA_NODE_H
